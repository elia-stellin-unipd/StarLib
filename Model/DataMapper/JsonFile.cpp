#include "JsonFile.h"

#include <QFile>
#include <QJsonDocument>
#include <QIODevice>

#include "Model/Converter/JsonConverter.h"

namespace Model::DataMapper {
    using namespace Model;

    JsonFile::JsonFile(const QString& path, bool autosave):
        _is_loaded(false), _has_unsaved_changes(false), _autosave(autosave), _path(path)
    {}

    QStringList JsonFile::load(Library& library) {
        QFile json_file(_path);
        if (!json_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            unload();
            throw FileError("Impossibile aprire file di libreria");
        }

        QByteArray data = json_file.readAll();
        json_file.close();

        QJsonParseError error;
        QJsonDocument document = QJsonDocument::fromJson(data, &error);
        _json = document.object();

        if (document.isNull()) {
            unload();
            throw FileError(error.errorString().toStdString());
        }
        else if (_json.isEmpty()) {
            unload();
            throw FileError("Il file di libreria è vuoto");
        }

        QStringList error_list;

        QString library_name = _json[Converter::Json::LIBRARY_NAME_FIELD].toString();
        library.clear();
        library.setName(library_name);

        QJsonValue library_articles_value = _json[Converter::Json::LIBRARY_ARTICLES_FIELD];
        if (library_articles_value.isNull() || library_articles_value.isUndefined()) {
            return error_list;
        }

        QJsonObject library_articles = library_articles_value.toObject();
        for (auto it = library_articles.constBegin(); it != library_articles.constEnd(); it++) {
            QString uuid_string = it.key();
            try {
                library.addArticle(Converter::Json::toObject(it->toObject(), uuid_string));
            }
            catch (const std::invalid_argument& e) {
                error_list.append(e.what());
            }
        }

        _is_loaded = true;

        return error_list;
    }

    void JsonFile::unload() {
        _is_loaded = false;
        _has_unsaved_changes = false;
        _json = QJsonObject();
        _path = "";
    }

    void JsonFile::save() {
        QByteArray byte_array = QJsonDocument(_json).toJson(QJsonDocument::Compact);

        QFile json_file(_path);
        if (!json_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            throw FileError("Impossibile aprire il file di libreria");
        }

        qint64 bytes = json_file.write(byte_array);
        json_file.close();

        if (bytes == -1) {
            throw FileError("C'è stato un errore nel salvataggio della libreria");
        }

        _has_unsaved_changes = false;
    }

    void JsonFile::addArticle(const AbstractArticle& article) {
        QString uuid = article.getUuid().toString(QUuid::WithoutBraces);
        const QJsonValue json_value = Converter::Json::fromObject(article);

        QVariantMap article_map = _json.toVariantMap().toStdMap().at(Converter::Json::LIBRARY_ARTICLES_FIELD)
                                      .toJsonObject().toVariantMap();
        article_map.insert(uuid, json_value.toVariant());
        _json[Converter::Json::LIBRARY_ARTICLES_FIELD] = QJsonObject::fromVariantMap(article_map);

        _has_unsaved_changes = true;
        if (_autosave) { save(); }
    }

    void JsonFile::deleteArticle(const AbstractArticle& article) {
        QString uuid = article.getUuid().toString(QUuid::WithoutBraces);
        const QJsonValue json_value = Converter::Json::fromObject(article);

        QVariantMap article_map = _json.toVariantMap().toStdMap().at(Converter::Json::LIBRARY_ARTICLES_FIELD)
                                      .toJsonObject().toVariantMap();
        article_map.remove(uuid);
        _json[Converter::Json::LIBRARY_ARTICLES_FIELD] = QJsonObject::fromVariantMap(article_map);

        _has_unsaved_changes = true;
        if (_autosave) { save(); }
    }

    void JsonFile::updateArticle(const AbstractArticle& article) {
        addArticle(article);
    }

    void JsonFile::setLibraryName(const QString& new_name) {
        _json.insert(Converter::Json::LIBRARY_NAME_FIELD, new_name);
        _has_unsaved_changes = true;
        if (_autosave) { save(); }
    }

    bool JsonFile::hasUnsavedChanges() const { return _has_unsaved_changes; }

    bool JsonFile::isAutosave() const { return _autosave; }
    void JsonFile::setAutosave(bool state) { _autosave = state; }

    const QString& JsonFile::getPath() const { return _path; }
    void JsonFile::setPath(const QString& path) { _path = path; }

    bool JsonFile::isLoaded() const { return _is_loaded; }
}
