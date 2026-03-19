#include "JsonReader.h"

#include <QJsonArray>

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

#include "Model/Converter/JsonConverter.h"


namespace Model::Converter::JsonReader {
    using namespace Helper;

    std::optional<QDate> readReleaseDate(const QJsonValue& value) {
        if (value.isNull() || value.isUndefined()) {
            return std::nullopt;
        }
        QJsonArray array = value.toArray();

        if (array.count() != 3) {
            return QDate();
        }

        return QDate(array.at(0).toInt(), array.at(1).toInt(), array.at(2).toInt());
    }

    QStringList readAuthors(const QJsonValue& value) {
        QStringList list;
        if (value.isNull() || value.isUndefined()) {
            return list; // lista vuota
        }

        QJsonArray array = value.toArray();
        for (auto author : array) {
            list.append(author.toString());
        }

        return list;
    }

    AbstractArticle *readBook(const QJsonObject& object, const QUuid& uuid) {
        return new Book(
            object.value(Json::TITLE_FIELD).toString(""),
            object.value(Json::DESCRIPTION_FIELD).toString(""),
            object.value(Json::FAVORITE_FIELD).toBool(),
            readReleaseDate(object.value(Json::RELEASE_DATE_FIELD)),
            readAuthors(object.value(Json::AUTHORS_FIELD)),
            object.value(Json::PUBLISHER_FIELD).toString(""),
            object.value(Json::PAGE_NUMBER_FIELD).toInt(),
            object.value(Json::ISBN_FIELD).toString(""),
            uuid
        );
    }

    AbstractArticle *readIssue(const QJsonObject& object, const QUuid& uuid) {
        return new MagazineIssue(
            object.value(Json::TITLE_FIELD).toString(""),
            object.value(Json::DESCRIPTION_FIELD).toString(""),
            object.value(Json::FAVORITE_FIELD).toBool(),
            readReleaseDate(object.value(Json::RELEASE_DATE_FIELD)),
            readAuthors(object.value(Json::AUTHORS_FIELD)),
            object.value(Json::PUBLISHER_FIELD).toString(""),
            object.value(Json::PAGE_NUMBER_FIELD).toInt(),
            object.value(Json::ISSN_FIELD).toString(""),
            object.value(Json::ISSUE_NUMBER_FIELD).toInt(),
            uuid
        );
    }

    AbstractArticle *readMovie(const QJsonObject& object, const QUuid& uuid) {
        return new Movie(
            object.value(Json::TITLE_FIELD).toString(""),
            object.value(Json::DESCRIPTION_FIELD).toString(""),
            object.value(Json::FAVORITE_FIELD).toBool(),
            readReleaseDate(object.value(Json::RELEASE_DATE_FIELD)),
            object.value(Json::DIRECTOR_FIELD).toString(""),
            MediaRuntime(object.value(Json::LENGTH_FIELD).toInt()),
            uuid
        );
    }

    AbstractArticle* read(const QJsonObject& object, const QUuid& uuid) {
        QJsonValue type_value = object.value("type");
        if (type_value.isUndefined()) {
            throw std::invalid_argument("Tipo di articolo mancante");
        }

        QString type = type_value.toString();
        if (type == Book::ARTICLE_TYPE) {
            return readBook(object, uuid);
        }
        else if (type == MagazineIssue::ARTICLE_TYPE) {
            return readIssue(object, uuid);
        }
        else if (type == Movie::ARTICLE_TYPE) {
            return readMovie(object, uuid);
        }
        else {
            throw std::invalid_argument("Tipo di articolo \"" + type.toStdString() + "\" sconosciuto");
        }
    }
}
