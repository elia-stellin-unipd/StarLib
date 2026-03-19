#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonObject>
#include <QStandardPaths>

namespace Model::Config {
    class Settings {
    private:
        static const QStandardPaths::StandardLocation config_location;
        static const QString AUTOSAVE_FIELD, LAST_OPENED_FIELD;
        static const QString CONFIG_FILENAME;

        QJsonObject json;

        void store();

    public:
        Settings();

        /// @brief Inizializza l'oggetto Settings, creando il file di configurazione
        /// per l'utente corrente in caso questo non esista.
        void init();

        QString getLastOpened() const;
        void setLastOpened(const QString& path);

        bool getAutosave() const;
        void setAutosave(bool state);

    };
}

#endif // SETTINGS_H
