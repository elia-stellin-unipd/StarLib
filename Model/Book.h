#ifndef BOOK_H
#define BOOK_H

#include "AbstractPublication.h"

namespace Model {

    class Book: public AbstractPublication {
    private:
        QString _ISBN;
    public:
        QString getArticleDisplayType() const override;
        QString getArticleType() const override;
        static const QString ARTICLE_TYPE;

        Book(
            const QString& title = "",
            const QString& description = "",
            bool is_favorite = false,
            const std::optional<QDate>& release_date = std::nullopt,
            const QStringList& authors = {},
            const QString& publisher = "",
            unsigned int page_number = 0,
            const QString& ISBN = "",
            const QUuid& uuid = QUuid::createUuid()
        );

        const QString& getISBN() const;
        void setISBN(const QString& ISBN);

        void accept(Visitors::ArticleConstVisitor *visitor) const override;
        void accept(Visitors::ArticleVisitor *visitor) override;

    };
    
};

#endif
