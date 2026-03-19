#ifndef FORMGENERATOR_H
#define FORMGENERATOR_H

#include <QFormLayout>

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

namespace Form {

    const QString
        TITLE("edit-form-title"),
        DESCRIPTION("edit-form-description"),
        RELEASE_DATE_CHECK("edit-form-date-check"),
        RELEASE_DATE_PICKER("edit-form-date-picker"),
        AUTHORS("edit-form-authors"),
        PUBLISHER("edit-form-publisher"),
        PAGE_NUMBER("edit-form-page-number"),
        ISBN("edit-form-isbn"),
        ISSUE_NUMBER("edit-form-issue-no"),
        ISSN("edit-form-issn"),
        DIRECTOR("edit-form-director"),
        RUNTIME_H("edit-form-runtime-h"),
        RUNTIME_MIN("edit-form-runtime-min"),
        RUNTIME_SEC("edit-form-runtime-sec");
    ;
    // NOTA: Non è stato creato un Visitor per semplicità, in quanto le funzioni vengono chiamate
    // esclusivamente da altri visitor
    void createBookForm(QFormLayout *form, const Model::Book *book = nullptr);
    void createIssueForm(QFormLayout *form, const Model::MagazineIssue *issue = nullptr);
    void createMovieForm(QFormLayout *form, const Model::Movie *movie = nullptr);

}

#endif // FORMGENERATOR_H
