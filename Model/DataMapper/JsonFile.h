#ifndef JSONFILE_H
#define JSONFILE_H

#include <string>
#include <QString>

#include "Model/Converter/JsonConverter.h"
#include "Model/Library.h"

namespace Model::DataMapper {

    class JsonFile
    {
    private:
        bool _is_loaded;
        bool _has_unsaved_changes;
        bool _autosave;
        QString _path;
        QJsonObject _json;

    public:
        explicit JsonFile(const QString& path = "", bool autosave = false);

        /// @brief Carica un file JSON, modificando la libreria passata per riferimento
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        /// @return QStringList - lista che contiene gli errori di eventuali articoli corrotti
        QStringList load(Model::Library& library);

        /// @brief Chiude la libreria
        void unload();

        /// @brief Salva l'oggetto JSON associato al file JSON
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        void save();

        // Azioni
        /// @brief Aggiunge un articolo al file JSON
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        void addArticle(const AbstractArticle& article);

        /// @brief Elimina un articolo dal file JSON
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        void deleteArticle(const AbstractArticle& article);

        /// @brief Aggiorna un articolo del file JSON
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        void updateArticle(const AbstractArticle& article);

        /// @brief Imposta il nome della libreria
        /// @throws JsonFile::FileError se non è possibile aprire il file specificato
        void setLibraryName(const QString& new_name);

        // Getter / setter
        bool hasUnsavedChanges() const;

        bool isAutosave() const;
        void setAutosave(bool state);

        const QString& getPath() const;
        void setPath(const QString& path);

        bool isLoaded() const;

        class FileError: public std::runtime_error {
        public:
            FileError(const std::string& w): std::runtime_error(w) {}
        };
    };

}

#endif // JSONFILE_H
