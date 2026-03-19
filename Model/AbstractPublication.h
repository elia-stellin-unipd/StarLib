#ifndef ABSTRACTPUBLICATION_H
#define ABSTRACTPUBLICATION_H

#include "AbstractArticle.h"
#include <QVector>

namespace Model {
    class AbstractPublication: public AbstractArticle {
    private:
        QStringList _authors;
        QString _publisher;
        unsigned int _page_number;

    public:
        AbstractPublication(
            const QString& title = "",
            const QString& description = "",
            bool is_favorite = false,
            const std::optional<QDate>& release_date = std::nullopt,
            const QStringList authors = {},
            const QString& publisher = "",
            unsigned int page_number = 0,
            const QUuid& uuid = QUuid::createUuid()
        );

        const QStringList& getAuthors() const;
        void setAuthors(const QStringList& author_list);

        const QString& getPublisher() const;
        void setPublisher(const QString& publisher);

        unsigned int getPageNumber() const;
        void setPageNumber(unsigned int page_number);
    };

};


#endif
