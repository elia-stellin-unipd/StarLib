#ifndef ABSTRACTARTICLE_H
#define ABSTRACTARTICLE_H

#include <optional>

#include <QDate>
#include <QString>
#include <QUuid>

#include "Visitors/ArticleConstVisitor.h"
#include "Visitors/ArticleVisitor.h"

namespace Model {

    class AbstractArticle {
    private:
        QUuid _uuid;
        QString _title;
        QString _description;
        bool _is_favorite;
        std::optional<QDate> _release_date;

    public:

        AbstractArticle(
            const QString& title = "",
            const QString& description = "",
            bool is_favorite = false,
            const std::optional<QDate>& release_date = std::nullopt,
            const QUuid& uuid = QUuid::createUuid()
        );
        virtual ~AbstractArticle() = default;

        void setUuid(const QUuid& uuid);
        const QUuid& getUuid() const;

        /// @return Titolo dell'articolo
        const QString& getTitle() const;

        /// @brief Imposta il titolo dell'articolo 
        /// @param title titolo
        void setTitle(const QString& title);

        /// @return Descrizione dell'articolo
        const QString& getDescription() const;

        /// @brief Imposta la descrizione dell'articolo
        /// @param description descrizinoe
        void setDescription(const QString& description);

        /// @return true se l'articolo è tra i preferiti, false altrimenti
        bool isFavorite() const;

        /// @brief Imposta flag preferiti dell'articolo
        /// @param is_favorite - Flag preferiti (true = preferito)
        void setFavorite(bool is_favorite);

        /// @return Data di rilascio dell'articolo, è std::nullopt se questa non è impostata
        const std::optional<QDate>& getReleaseDate() const;

        /// @brief Imposta data di rilascio dell'articolo
        /// @param date - Data di rilascio
        void setReleaseDate(QDate date);

        /// @brief Rimuove la data di rilascio
        void unsetReleaseDate();

        /// @return true se la data di rilascio è impostata
        bool isReleaseDateSet() const;

        /// @brief Ritorna il tipo dell'articolo. Viene utilizzato solamente per eventuali
        /// stampe a schermo, non per fare controlli di RTTI
        virtual QString getArticleDisplayType() const = 0;

        /// @brief Ritorna il tipo dell'articolo usato come identificatore nei file
        /// JSON serializzati.
        virtual QString getArticleType() const = 0;

        /// @brief Ritorna il nome intero dell'articolo (usato nella status bar)
        QString getFullName() const;

        /// @brief Accetta ed esegue il codice di visitor di tipo ArticleVisitor 
        /// @param visitor visitor da eseguire
        virtual void accept(Visitors::ArticleConstVisitor *visitor) const = 0;
        virtual void accept(Visitors::ArticleVisitor *visitor) = 0;
    };
};
#endif
