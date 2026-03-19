#ifndef JSONREADER_H
#define JSONREADER_H

#include <QJsonObject>
#include <QUuid>

#include "Model/AbstractArticle.h"

namespace Model::Converter::JsonReader {

    AbstractArticle* read(const QJsonObject& object, const QUuid& uuid);
}

#endif // JSONREADER_H
