#include "InfoBase.h"

#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QScrollArea>

#include "Utils/Style.h"
#include "View/FavoriteButton.h"

using namespace Model;
using namespace Utils::Style::Icons;

InfoBase::InfoBase(const AbstractArticle& article, QWidget *parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    QVBoxLayout *vbox = new QVBoxLayout(this);

        // Header
        QHBoxLayout *header = new QHBoxLayout();

            // Titolo
            QLabel *title = new QLabel(article.getTitle());
            title->setWordWrap(true);
            title->setObjectName("info-article-title"); // Vd. InfoView.qss
            header->setAlignment(title, Qt::AlignBottom);

            header->addWidget(title);

            // Bottone preferiti
            FavoriteButton *favorite_button = new FavoriteButton(article.isFavorite());
            header->addWidget(favorite_button);

            // Bottone modifica
            QPushButton *edit_button = new QPushButton();
                edit_button->setObjectName("info-edit-article");
                edit_button->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
                edit_button->setIcon(QIcon(EDIT_GRAY));
                edit_button->setIconSize(QSize(20, 20));
                edit_button->setToolTip(QString("Modifica %1").arg(article.getTitle()));

                connect(
                    edit_button, &QPushButton::pressed, this, &InfoBase::requestOpenEditorCurrent
                );
            header->addWidget(edit_button);

        vbox->addLayout(header);

        // Label sotto l'header
        QLabel *type = new QLabel(
            QString("(%1)").arg(article.getArticleDisplayType())
        );
            type->setObjectName("info-article-type");
        vbox->addWidget(type);

        // Form (informazioni principali)
        QFormLayout *form = new QFormLayout();
        //form->setRowWrapPolicy(QFormLayout::WrapLongRows)

        if (article.getDescription().length() > 100) {
            QTextEdit *description = new QTextEdit(article.getDescription());
            description->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
            description->setWordWrapMode(QTextOption::WordWrap);
            description->setReadOnly(true);
            description->setStyleSheet("QTextEdit { background: transparent;}");
            form->addRow("Descrizione", description);
        }
        else {
            QLabel *description = new QLabel(article.getDescription());
            description->setWordWrap(true);
            form->addRow("Descrizione", description);
        }


        if (article.isReleaseDateSet()) {
            form->addRow("Data di rilascio", new QLabel(
                article.getReleaseDate()->toString("dd/MM/yyyy"))
            );
        }

        vbox->addLayout(form);

    // Nota: Qua verranno aggiunti altri dati dai visitor

    _form = form;

    // Segnali ///////

    // InfoBase -> InfoView
    connect(
        favorite_button, &QPushButton::pressed,
        this, &InfoBase::requestFavoriteCurrent
        );

    // InfoBase -> InfoBase
    connect(
        this, &InfoBase::changeFavoriteButtonState,
        favorite_button, &FavoriteButton::changeState
        );
}

QFormLayout *InfoBase::mainLayout() const {
    return _form;
}

void InfoBase::onResultFavoriteArticle(QWeakPointer<AbstractArticle> article) {
    emit changeFavoriteButtonState(article.toStrongRef()->isFavorite());
}
