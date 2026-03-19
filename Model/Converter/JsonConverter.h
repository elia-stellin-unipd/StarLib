#ifndef JSONCONVERTER_H
#define JSONCONVERTER_H

#include <QString>

#include "Model/Converter/JsonReader.h"
#include "Model/AbstractArticle.h"

/// @brief Wrapper che permette conversione da e verso file JSON
namespace Model::Converter::Json {
    const QString
        LIBRARY_NAME_FIELD("name"),
        LIBRARY_ARTICLES_FIELD("articles"),
        TYPE_FIELD("type"),
        TITLE_FIELD("title"),
        DESCRIPTION_FIELD("description"),
        FAVORITE_FIELD("favorite"),
        RELEASE_DATE_FIELD("release_date"),
        AUTHORS_FIELD("authors"),
        PUBLISHER_FIELD("publisher"),
        PAGE_NUMBER_FIELD("page_number"),
        ISBN_FIELD("isbn"),
        ISSN_FIELD("issn"),
        ISSUE_NUMBER_FIELD("issue_number"),
        DIRECTOR_FIELD("director"),
        LENGTH_FIELD("length")
    ;

    QJsonObject fromObject(const AbstractArticle& article);
    AbstractArticle *toObject(const QJsonObject& json, const QString& uuid_string);

}
#endif // JSONCONVERTER_H
