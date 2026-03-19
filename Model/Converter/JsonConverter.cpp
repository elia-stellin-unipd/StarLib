#include "JsonConverter.h"

#include "JsonReader.h"
#include "JsonVisitor.h"

#include <QUuid>

namespace Model::Converter::Json {

    QJsonObject fromObject(const AbstractArticle& article) {
        JsonVisitor visitor;
        article.accept(&visitor);
        return visitor.getObject();
    }

    AbstractArticle *toObject(const QJsonObject& json, const QString& uuid_string) {
        return JsonReader::read(json, QUuid::fromString(uuid_string));
    }
}
