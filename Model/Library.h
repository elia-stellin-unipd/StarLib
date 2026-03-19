#ifndef LIBRARY_H
#define LIBRARY_H

#include "AbstractArticle.h"
#include <QList>
#include <QString>
#include <QPointer>
#include <QSharedPointer>

namespace Model {
    class Library {
    private:
        QString _name;
        QList<QSharedPointer<AbstractArticle>> _articles; // Shared pointer, perché solo la Library ha la ownership degli articoli

    public:
        Library(
            const QString& name = "",
            const QList<QSharedPointer<AbstractArticle>>& articles = {}
        );

        const QList<QSharedPointer<AbstractArticle>>& getArticles() const;

        /// @brief Aggiungi articolo alla libreria in memoria
        QWeakPointer<AbstractArticle> addArticle(AbstractArticle* article);

        /// @brief Rimuovi articolo usando puntatore weak
        /// La funzione si occupa di impostare lo shared pointer relativo a null
        void deleteArticle(QWeakPointer<AbstractArticle> article);

        /// @brief Elimina tutti gli elementi della libreria e ne imposta il nome
        /// alla stringa vuota
        void clear();

        const QString& getName() const;
        qsizetype getCount() const;
        void setName(const QString& name);
    };
}
#endif // LIBRARY_H
