#include "EditArticleVisitor.h"

#include <QCheckBox>
#include <QDateEdit>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

#include "View/Form/FormGenerator.h"


namespace Visitors {

using namespace Model;

EditArticleVisitor::EditArticleVisitor(QWidget* base_form) {
    if (!base_form) {
        qErrnoWarning("Widget must be non-null when passing to EditArticleVisitor");
        return;
    }
    form = base_form;
}

void EditArticleVisitor::setupBaseArticle(AbstractArticle& article) {
    // Titolo
    QLineEdit *title_edit = form->findChild<QLineEdit*>(Form::TITLE);
    if (title_edit) {
        article.setTitle(title_edit->text());
    }

    // Descrizione
    QTextEdit *text_edit = form->findChild<QTextEdit*>(Form::DESCRIPTION);
    if (text_edit) {
        article.setDescription(text_edit->toPlainText());
    }

    // Data rilascio
    QCheckBox *date_check = form->findChild<QCheckBox*>(Form::RELEASE_DATE_CHECK);
    if (date_check) {
        if (date_check->isChecked()) {
            QDateEdit *date_edit = form->findChild<QDateEdit*>(Form::RELEASE_DATE_PICKER);
            if (date_edit) {
                article.setReleaseDate(date_edit->date());
            }
        }
        else {
            article.unsetReleaseDate();
        }
    }
}

void EditArticleVisitor::setupPublication(AbstractPublication& publication) {
    setupBaseArticle(publication);

    // Autori
    QLineEdit *authors_edit = form->findChild<QLineEdit*>(Form::AUTHORS);
    if (authors_edit) {
        QStringList author_list = authors_edit->text().split(
            QRegularExpression(R"(\s*,\s*)")
        );

        publication.setAuthors(author_list);
    }

    // Editore
    QLineEdit *publisher_edit = form->findChild<QLineEdit*>(Form::PUBLISHER);
    if (publisher_edit) {
        publication.setPublisher(publisher_edit->text());
    }

    // Numero pagine
    QSpinBox *page_no_spin = form->findChild<QSpinBox*>(Form::PAGE_NUMBER);
    if (page_no_spin) {
        publication.setPageNumber(page_no_spin->value());
    }
}


void EditArticleVisitor::visit(Book &book) {
    setupPublication(book);

    // ISBN
    QLineEdit *isbn_edit = form->findChild<QLineEdit*>(Form::ISBN);

    if (isbn_edit) {
        book.setISBN(isbn_edit->text());
    }
}

void EditArticleVisitor::visit(MagazineIssue &issue) {
    setupPublication(issue);

    // Numero uscita
    QSpinBox *issue_no_spin = form->findChild<QSpinBox*>(Form::ISSUE_NUMBER);
    if (issue_no_spin) {
        issue.setIssueNumber(issue_no_spin->value());
    }

    // ISSN
    QLineEdit *issn_edit = form->findChild<QLineEdit*>(Form::ISSN);
    if (issn_edit) {
        issue.setISSN(issn_edit->text());
    }
}

void EditArticleVisitor::visit(Movie &movie) {
    setupBaseArticle(movie);

    // Regista
    QLineEdit *director_edit = form->findChild<QLineEdit*>(Form::DIRECTOR);
    if (director_edit) {
        movie.setDirector(director_edit->text());
    }

    // Lunghezza film
    Helper::MediaRuntime runtime = movie.getLength();
    uint64_t hours = runtime.getHours(),
             minutes = runtime.getMinutes(),
             seconds = runtime.getSeconds();

    // - Ore
    QSpinBox *runtime_h_spin = form->findChild<QSpinBox*>(Form::RUNTIME_H);
    if (runtime_h_spin) {
        hours = runtime_h_spin->value();
    }

    // - Minuti
    QSpinBox *runtime_min_spin = form->findChild<QSpinBox*>(Form::RUNTIME_MIN);
    if (runtime_min_spin) {
        minutes = runtime_min_spin->value();
    }

    QSpinBox *runtime_sec_spin = form->findChild<QSpinBox*>(Form::RUNTIME_SEC);
    if (runtime_sec_spin) {
        seconds = runtime_sec_spin->value();
    }
    movie.setLength(Helper::MediaRuntime(hours, minutes, seconds));
}

}
