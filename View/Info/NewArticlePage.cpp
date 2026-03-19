#include "NewArticlePage.h"

#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QSpacerItem>
#include <QShortcut>
#include <QVBoxLayout>

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

#include "Utils/Layout.h"
#include "Utils/Style.h"

#include "View/Dialog/ConfirmDialogBox.h"
#include "View/Form/FormGenerator.h"
#include "View/Form/FormValidator.h"

#include "Visitors/EditArticleVisitor.h"

using namespace Utils::Style::Icons;

NewArticlePage::NewArticlePage(QWidget *parent):
    QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Setup della pagina
    // Titolo
    QLabel *title = new QLabel(QString("Nuovo articolo"));
    title->setWordWrap(true);
    title->setObjectName("info-article-title");
    vbox->addWidget(title);

    // Combo Box per tipo di articolo
    QFormLayout *combo_box_form = new QFormLayout();
    QComboBox *article_type_combo = new QComboBox();

    article_type_combo->setInsertPolicy(QComboBox::InsertAlphabetically);
    // NOTA: non cambiare ordine. Ordine dev'essere alfabetico!
    article_type_combo->addItem(QIcon(BOOK), "Libro", ArticleType::Book);
    article_type_combo->addItem(QIcon(FILM), "Film", ArticleType::Movie);
    article_type_combo->addItem(QIcon(NEWSPAPER), "Uscita di rivista", ArticleType::Issue);

    combo_box_form->addRow("Tipo articolo", article_type_combo);
    vbox->addLayout(combo_box_form);

    QStackedLayout *stack = new QStackedLayout();
    stack->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // NOTA: non cambiare ordine. Ordine deve seguire ordine nel combo box!
    QWidget *book_page = new QWidget();
    book_page->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
    _book_form = new QFormLayout(book_page);
    stack->addWidget(book_page);

    QWidget *movie_page = new QWidget();
    _movie_form = new QFormLayout(movie_page);
    stack->addWidget(movie_page);

    QWidget *issue_page = new QWidget();
    _issue_form = new QFormLayout(issue_page);
    stack->addWidget(issue_page);

    build();


    vbox->addLayout(stack);

    connect(
        article_type_combo, &QComboBox::activated,
        this, [=](int index) {
            bool ok;
            int enum_index = article_type_combo->itemData(index).toInt(&ok);
            if (!ok) {
                return;
            }
            switch (enum_index) {
            case ArticleType::Book:
                stack->setCurrentWidget(book_page);
                break;
            case ArticleType::Issue:
                stack->setCurrentWidget(issue_page);
                break;
            case ArticleType::Movie:
                stack->setCurrentWidget(movie_page);
                break;
            }

        });

    QHBoxLayout *button_layout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    QPushButton *confirm = new QPushButton("Conferma");
    confirm->setObjectName("confirm-button");
    connect(
        confirm, &QPushButton::pressed,
        [=] {
            using namespace Visitors;
            bool ok;
            int enum_index = article_type_combo->currentData().toInt(&ok);
            if (!ok) {
                return;
            }

            QFormLayout *target_form;
            Model::AbstractArticle *article;
            switch (enum_index) {
            case ArticleType::Book: {
                target_form = _book_form;
                article = new Model::Book;
                break;
            }
            case ArticleType::Issue: {
                target_form = _issue_form;
                article = new Model::MagazineIssue;
                break;
            }
            case ArticleType::Movie: {
                target_form = _movie_form;
                article = new Model::Movie;
                break;
            }
            default:
                qWarning() << "Trying to conferm for non-existent article";
                return;
            }

            if (!Form::validate(target_form)) { return; }
            EditArticleVisitor visitor(target_form->parentWidget());
            article->accept(&visitor);

            emit requestAddArticle(article);

        }
    );
    button_layout->addWidget(confirm);

    QPushButton *cancel = new QPushButton("Annulla");
    connect(
        cancel, &QPushButton::pressed,
        this, & NewArticlePage::onRequestCancelNewArticle
    );
    button_layout->addWidget(cancel);

    vbox->addLayout(button_layout);

    new QShortcut(
        QKeySequence(Qt::Key_Escape),
        this,
        [=]{ onRequestCancelNewArticle(); }
    );
}

void NewArticlePage::build() {
    using namespace Utils::Layout;

    clear(_book_form);
    clear(_movie_form);
    clear(_issue_form);

    Form::createBookForm(_book_form);
    Form::createMovieForm(_movie_form);
    Form::createIssueForm(_issue_form);
}

void NewArticlePage::onRequestCancelNewArticle() {
    ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare la creazione?");
    if (!confirm.ask()) { return; }
    emit resultCancelNewArticle();
}


