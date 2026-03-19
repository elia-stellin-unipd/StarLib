#include "JsonVisitor.h"

#include <QJsonArray>

#include "Model/Converter/JsonConverter.h"

namespace Model::Converter {
    using namespace Model;

    QJsonObject JsonVisitor::getObject() const {
        return json_object;
    }

    void JsonVisitor::convertBase(const AbstractArticle& article) {
        json_object = QJsonObject();
        json_object.insert(Json::TYPE_FIELD, QJsonValue::fromVariant(article.getArticleType()));
        json_object.insert(Json::TITLE_FIELD, QJsonValue::fromVariant(article.getTitle()));
        json_object.insert(Json::DESCRIPTION_FIELD, QJsonValue::fromVariant(article.getDescription()));
        json_object.insert(Json::FAVORITE_FIELD, QJsonValue::fromVariant(article.isFavorite()));

        if (article.isReleaseDateSet()) {
            QDate article_date = article.getReleaseDate().value();
            json_object.insert(
                Json::RELEASE_DATE_FIELD,
                QJsonArray({
                    article_date.year(),
                    article_date.month(),
                    article_date.day()
                })
            );
        }
        else {
            json_object.insert(Json::RELEASE_DATE_FIELD, QJsonValue()); // null
        }
    }

    void JsonVisitor::convertPublication(const AbstractPublication& publication) {
        convertBase(publication);
        json_object.insert(Json::AUTHORS_FIELD, QJsonArray::fromStringList(publication.getAuthors()));
        json_object.insert(Json::PUBLISHER_FIELD, QJsonValue::fromVariant(publication.getPublisher()));
        json_object.insert(Json::PAGE_NUMBER_FIELD, QJsonValue::fromVariant(publication.getPageNumber()));
    }

    void JsonVisitor::visit(const Book& book) {
        convertPublication(book);
        json_object.insert(Json::ISBN_FIELD, QJsonValue::fromVariant(book.getISBN()));
    }
    void JsonVisitor::visit(const MagazineIssue& issue) {
        convertPublication(issue);
        json_object.insert(Json::ISSN_FIELD, QJsonValue::fromVariant(issue.getISSN()));
        json_object.insert(Json::ISSUE_NUMBER_FIELD, QJsonValue::fromVariant(issue.getIssueNumber()));
    }
    void JsonVisitor::visit(const Movie& movie) {
        convertBase(movie);
        json_object.insert(Json::DIRECTOR_FIELD, QJsonValue::fromVariant(movie.getDirector()));
        json_object.insert(Json::LENGTH_FIELD, QJsonValue::fromVariant((unsigned long long) movie.getLength().getTotalSeconds()));
    }
}
