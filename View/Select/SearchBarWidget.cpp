#include "SearchBarWidget.h"

#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPalette>
#include <QStyle>

#include <QDebug>

#include "Model/Search/Query.h"
#include "View/Layouts/FlowLayout.h"
#include "Utils/Style.h"

SearchBarWidget::SearchBarWidget(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // Barra di ricerca ///////////////
    _line_edit = new QLineEdit();
    _line_edit->setPlaceholderText("Cerca articolo...");

    layout->addWidget(_line_edit);

    // Trucco per far funzionare lo stile della SearchBar
    // https://stackoverflow.com/a/54887161/change-color-of-placeholder-text-in-qlineedit
    /* La stylesheet di QLineEdit è
     * QLineEdit { color: white; }
     * QLineEdit[text=\"\"] {color: gray; }
    */
    setStyleSheet(Utils::Style::load(":/assets/style/SearchBarWidget.qss"));
    connect(
        _line_edit, &QLineEdit::textChanged,
        this, [=]{ style()->polish(_line_edit);}
    );

    connect(_line_edit, &QLineEdit::textChanged, [=] { emitSearch(); });

    // Bottoni per opzioni /////////////////////
    using namespace Utils::Style;
    using namespace View::Layouts;
    FlowLayout *button_layout = new FlowLayout();
    layout->addLayout(button_layout);

    QCheckBox *book_checkbox = new QCheckBox("&Libro");
    book_checkbox->setObjectName("search_bar_book");
    book_checkbox->setIcon(QIcon(Icons::BOOK));

    QCheckBox *movie_checkbox = new QCheckBox("F&ilm");
    movie_checkbox->setObjectName("search_bar_movie");
    movie_checkbox->setIcon(QIcon(Icons::FILM));

    QCheckBox *issue_checkbox = new QCheckBox("&Uscita rivista");
    issue_checkbox->setObjectName("search_bar_issue");
    issue_checkbox->setIcon(QIcon(Icons::NEWSPAPER));

    QCheckBox *favorite_checkbox = new QCheckBox();
    favorite_checkbox->setObjectName("search_bar_favorite");
    favorite_checkbox->setIcon(QIcon(Icons::FAVORITE_ON));

    _options = {
        book_checkbox,
        movie_checkbox,
        issue_checkbox,
        favorite_checkbox
    };

    for (auto option : _options) {
        option->setCheckState(Qt::Checked);
        button_layout->addWidget(option);
        connect(option, &QCheckBox::stateChanged, [=] { emitSearch(); });
    }

    favorite_checkbox->setCheckState(Qt::Unchecked);
}

// SLOT ////////////////////////////
void SearchBarWidget::setFocus() {
    _line_edit->setFocus();
}

// SEGNALI /////////////////////
void SearchBarWidget::emitSearch() {
    using namespace Model::Search;

    QCheckBox* book_checkbox = findChild<QCheckBox*>("search_bar_book");
    QCheckBox* movie_checkbox = findChild<QCheckBox*>("search_bar_movie");
    QCheckBox* issue_checkbox = findChild<QCheckBox*>("search_bar_issue");
    QCheckBox* favorite_checkbox = findChild<QCheckBox*>("search_bar_favorite");

    if (!(book_checkbox && movie_checkbox && issue_checkbox && favorite_checkbox)) {
        qWarning() << "aaaa";
        return;
    }

    Query query(
        _line_edit->text(),
        book_checkbox->checkState(),
        movie_checkbox->checkState(),
        issue_checkbox->checkState(),
        favorite_checkbox->checkState()
    );

    emit searchQuery(query);
}

