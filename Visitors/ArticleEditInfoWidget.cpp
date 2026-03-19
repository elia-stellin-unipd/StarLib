#include "ArticleEditInfoWidget.h"

#include <QCheckBox>
#include <QDateEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSizePolicy>
#include <QSpinBox>
#include <QStyle>
#include <QTextEdit>


#include "Model/Book.h"
#include "Model/Movie.h"
#include "Model/MagazineIssue.h"

#include "View/Form/FormGenerator.h"

namespace Visitors {
    using namespace Model;

    EditInfoBase* ArticleEditInfoWidget::getWidget() const {
        return widget;
    }

    void ArticleEditInfoWidget::connectBase() {
        QLineEdit *edit_title = widget->findChild<QLineEdit*>(Form::TITLE);
        QTextEdit *edit_description = widget->findChild<QTextEdit*>(Form::DESCRIPTION);
        QCheckBox *select_date = widget->findChild<QCheckBox*>(Form::RELEASE_DATE_CHECK);
        QDateEdit *edit_date = widget->findChild<QDateEdit*>(Form::RELEASE_DATE_PICKER);
        
        if (edit_title) {            
            widget->connect(
                edit_title, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }
        
        if (edit_description) {            
            widget->connect(
                edit_description, &QTextEdit::textChanged,
                widget, &EditInfoBase::onEdit
            );
        }
        
        if (edit_date) {
            widget->connect(
                edit_date, &QDateEdit::dateChanged,
                widget, &EditInfoBase::onEdit
            );            
        }
        
        if (select_date && edit_date) {
            widget->connect(
                select_date, &QCheckBox::stateChanged,
                widget, &EditInfoBase::onEdit
            );
        }
    }
    
    void ArticleEditInfoWidget::connectPublication() {
        connectBase();
        QLineEdit *edit_authors = widget->findChild<QLineEdit*>(Form::AUTHORS);
        QLineEdit *edit_publisher = widget->findChild<QLineEdit*>(Form::AUTHORS);
        QSpinBox *edit_page_no = widget->findChild<QSpinBox*>(Form::PAGE_NUMBER);
        
        if (edit_authors) {            
            widget->connect(
                edit_authors, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }
        
        if (edit_publisher) {            
            widget->connect(
                edit_publisher, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }
        
        if (edit_page_no) {            
            widget->connect(
                edit_page_no, &QSpinBox::valueChanged,
                widget, &EditInfoBase::onEdit
            );
        }
    }
    
    void ArticleEditInfoWidget::connectBook() {
        connectPublication();
        QLineEdit *edit_isbn = widget->findChild<QLineEdit*>(Form::ISBN);
        
        if (edit_isbn) {
            widget->connect(
                edit_isbn, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }
    }
    
    void ArticleEditInfoWidget::connectIssue() {
        connectPublication();
        QLineEdit *edit_issn = widget->findChild<QLineEdit*>(Form::ISSN);
        QSpinBox *edit_issue_no = widget->findChild<QSpinBox*>(Form::ISSUE_NUMBER);
        
        if (edit_issue_no) {
            widget->connect(
                edit_issue_no, &QSpinBox::valueChanged,
                widget, &EditInfoBase::onEdit
            );
        }

        if (edit_issn) {
            widget->connect(
                edit_issn, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }
    }

    void ArticleEditInfoWidget::connectMovie() {
        QLineEdit *edit_director = widget->findChild<QLineEdit*>(Form::DIRECTOR);
        QSpinBox *edit_h = widget->findChild<QSpinBox*>(Form::RUNTIME_H);
        QSpinBox *edit_min = widget->findChild<QSpinBox*>(Form::RUNTIME_MIN);
        QSpinBox *edit_sec = widget->findChild<QSpinBox*>(Form::RUNTIME_SEC);

        if (edit_director) {
            widget->connect(
                edit_director, &QLineEdit::textEdited,
                widget, &EditInfoBase::onEdit
            );
        }

        if (edit_h) {
            widget->connect(
                edit_h, &QSpinBox::valueChanged,
                widget, &EditInfoBase::onEdit
            );
        }

        if (edit_min) {
            widget->connect(
                edit_min, &QSpinBox::valueChanged,
                widget, &EditInfoBase::onEdit
            );
        }

        if (edit_sec) {
            widget->connect(
                edit_sec, &QSpinBox::valueChanged,
                widget, &EditInfoBase::onEdit
            );
        }
    }

    void ArticleEditInfoWidget::visit(const Book& book) {
        widget = new EditInfoBase(book);
        Form::createBookForm(widget->mainLayout(), &book);
        connectBook();
    }

    void ArticleEditInfoWidget::visit(const MagazineIssue& issue) {
        widget = new EditInfoBase(issue);
        Form::createIssueForm(widget->mainLayout(), &issue);
        connectIssue();
    }

    void ArticleEditInfoWidget::visit(const Movie& movie) {
        widget = new EditInfoBase(movie);;
        Form::createMovieForm(widget->mainLayout(), &movie);
        connectMovie();
    }

};
