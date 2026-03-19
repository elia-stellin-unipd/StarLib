#include "FormGenerator.h"

#include <QTextEdit>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QDateEdit>
#include <QCheckBox>

using namespace Model;

namespace Form {

    namespace {
    static void createBaseArticleForm(QFormLayout *form, const AbstractArticle *article) {
        form->setFormAlignment(Qt::AlignTop | Qt::AlignLeft);
        form->setRowWrapPolicy(QFormLayout::WrapLongRows);

        QLineEdit *edit_title = new QLineEdit(
            article? article->getTitle() : ""
        );
        edit_title->setObjectName(TITLE);
        form->addRow("Titolo", edit_title);

        QTextEdit *edit_description = new QTextEdit(
            article? article->getDescription() : ""
        );
        edit_description->setObjectName(DESCRIPTION);
        edit_description->setAcceptRichText(false);
        edit_description->setTabChangesFocus(true);
        form->addRow("Descrizione", edit_description);

        QHBoxLayout *date_layout = new QHBoxLayout();
        date_layout->setAlignment(Qt::AlignLeft);
        form->addRow("Data di rilascio", date_layout);

        QCheckBox *select_date = new QCheckBox();
        select_date->setObjectName(RELEASE_DATE_CHECK);
        select_date->setCheckState(
            article && article->isReleaseDateSet()? Qt::Checked : Qt::Unchecked
        );
        date_layout->addWidget(select_date);

        QDateEdit *edit_date = new QDateEdit();
        edit_date->setObjectName(RELEASE_DATE_PICKER);
        if (article && article->isReleaseDateSet()) {
            edit_date->setDate(article->getReleaseDate().value());
        }
        else {
            edit_date->setDate(QDate::currentDate());
            edit_date->hide();
        }

        select_date->connect(
            select_date, &QCheckBox::stateChanged,
            [=](int state) {
                if (state == Qt::Checked) { edit_date->show(); }
                else { edit_date->hide(); }
            }
        );

        date_layout->addWidget(edit_date);
    }

    static void createPublicationForm(QFormLayout *form, const AbstractPublication *publication) {
        createBaseArticleForm(form, publication);

        QLineEdit *edit_authors = new QLineEdit(
            publication? publication->getAuthors().join(", ") : ""
        );
        edit_authors->setObjectName(AUTHORS);
        form->addRow("Autori\n(separati da virgola)", edit_authors);

        QLineEdit *edit_publisher = new QLineEdit(
            publication? publication->getPublisher() : ""
        );
        edit_publisher->setObjectName(PUBLISHER);
        form->addRow("Editore", edit_publisher);

        QSpinBox *edit_page_no = new QSpinBox();
        edit_page_no->setObjectName(PAGE_NUMBER);
        edit_page_no->setMinimum(0);
        edit_page_no->setMaximum(999999);
        edit_page_no->setValue(publication? publication->getPageNumber() : 0);
        edit_page_no->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        form->addRow("Numero di pagine", edit_page_no);
    }
    }

void createBookForm(QFormLayout *form, const Book *book) {
    createPublicationForm(form, book);

    QLineEdit *edit_isbn = new QLineEdit(
        book? book->getISBN() : ""
    );
    edit_isbn ->setObjectName(ISBN);
    form->addRow("ISBN", edit_isbn);
}

void createIssueForm(QFormLayout *form, const MagazineIssue *issue) {
    createPublicationForm(form, issue);

    QSpinBox *issue_no = new QSpinBox();
    issue_no->setObjectName(ISSUE_NUMBER);
    issue_no->setValue(issue? issue->getIssueNumber() : 0);
    issue_no->setMinimum(0);
    issue_no->setMaximum(999999);
    issue_no->setPrefix("#");
    form->addRow("Numero d'uscita", issue_no);

    QLineEdit *edit_issn = new QLineEdit(issue? issue->getISSN() : "");
    edit_issn->setObjectName(ISSN);
    form->addRow("ISSN", edit_issn);
}

void createMovieForm(QFormLayout *form, const Movie *movie) {
    createBaseArticleForm(form, movie);

    QLineEdit *director = new QLineEdit(movie? movie->getDirector() : "");
    director->setObjectName(DIRECTOR);
    form->addRow("Regista", director);

    // Imposta lunghezza film
    QHBoxLayout *runtime_layout = new QHBoxLayout();
    runtime_layout->setAlignment(Qt::AlignLeft | Qt::AlignCenter);

    QSpinBox *edit_h = new QSpinBox();
    edit_h->setObjectName(RUNTIME_H);
    edit_h->setValue(movie? movie->getLength().getHours() : 0);
    edit_h->setMinimum(0);
    edit_h->setMaximum(999);
    edit_h->setSuffix(" h");
    runtime_layout->addWidget(edit_h);

    QSpinBox *edit_min = new QSpinBox();
    edit_min->setObjectName(RUNTIME_MIN);
    edit_min->setValue(movie? movie->getLength().getMinutes() : 0);
    edit_min->setMinimum(0);
    edit_min->setMaximum(59);
    edit_min->setSuffix(" min");
    runtime_layout->addWidget(edit_min);

    QSpinBox *edit_sec = new QSpinBox();
    edit_sec->setObjectName(RUNTIME_SEC);
    edit_sec->setValue(movie? movie->getLength().getSeconds() : 0);
    edit_sec->setMinimum(0);
    edit_sec->setMaximum(59);
    edit_sec->setSuffix(" sec");
    runtime_layout->addWidget(edit_sec);

    form->addRow("Durata", runtime_layout);
}
}
