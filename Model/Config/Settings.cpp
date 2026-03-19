#include "Settings.h"

#include <QFile>
#include <QJsonDocument>
#include <QDir>


namespace Model::Config {
    const QStandardPaths::StandardLocation
        Settings::config_location(QStandardPaths::AppConfigLocation);

    const QString
        Settings::AUTOSAVE_FIELD("autosave"),
        Settings::LAST_OPENED_FIELD("last_opened");

    const QString Settings::CONFIG_FILENAME("config.json");

    Settings::Settings() {}

    void Settings::init() {
        // Locate config file
        QString located_path = QStandardPaths::locate(config_location, CONFIG_FILENAME);

        if (located_path.isEmpty()) {
            // File non presente => app aperta per la prima volta, crealo.
            QString writable_location = QStandardPaths::writableLocation(config_location);

            if (!writable_location.isEmpty()) {
                QDir writable_dir = QDir(writable_location);

                if (!writable_dir.exists()) {
                    writable_dir.mkpath(writable_dir.absolutePath());
                }

                QJsonObject default_settings;
                default_settings.insert(LAST_OPENED_FIELD, QString(""));
                default_settings.insert(AUTOSAVE_FIELD, false);
                json = default_settings;

                QJsonDocument config_doc(default_settings);
                QByteArray config_content(config_doc.toJson(QJsonDocument::Compact));

                QString config_file_path(writable_dir.absoluteFilePath(CONFIG_FILENAME));
                QFile config_file(config_file_path);

                if (config_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                    config_file.write(config_content);
                }
                else {
                    qWarning() << "error trying to open config file";
                }
            }
            else {
                qWarning() << "cannot find writable location for config file";
            }
        }

        else {
            // Ricerca ultima libreria aperta all'interno del config file
            QFile config_file(located_path);
            QByteArray config_file_content;
            if (config_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                config_file_content = config_file.readAll();
                config_file.close();
            }
            else {
                qWarning() << "cannot open config file at path" << located_path;
            }

            QJsonDocument config_document = QJsonDocument::fromJson(config_file_content);

            if (!config_document.isNull()) {
                json = config_document.object();
            }
            else {
                json = QJsonObject();
            }

        }
    }

    void Settings::store() {
        QString located_path = QStandardPaths::locate(config_location, CONFIG_FILENAME);

        if (located_path.isEmpty()) {
            QString writable_location = QStandardPaths::writableLocation(config_location);

            if (!writable_location.isEmpty()) {
                QDir writable_dir = QDir(writable_location);

                if (!writable_dir.exists()) {
                    writable_dir.mkpath(writable_dir.absolutePath());
                }

                located_path = writable_dir.absoluteFilePath(CONFIG_FILENAME);
            }
            else {
                qWarning() << "cannot find writable location for config file";
                return;
            }
        }

        QJsonDocument doc(json);
        QByteArray config_content(doc.toJson(QJsonDocument::Compact));
        QFile config_file(located_path);

        if (config_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            config_file.write(config_content);
        }
    }

    QString Settings::getLastOpened() const {
        return json[LAST_OPENED_FIELD].toString();
    }

    void Settings::setLastOpened(const QString& path) {
        json.insert(LAST_OPENED_FIELD, path);
        store();
    }

    bool Settings::getAutosave() const {
        return json[AUTOSAVE_FIELD].toBool();
    }

    void Settings::setAutosave(bool state) {
        json[AUTOSAVE_FIELD] = state;
        store();
    }
}
