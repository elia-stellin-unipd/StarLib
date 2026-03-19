#include "AbstractPublication.h"

namespace Model {

    AbstractPublication::AbstractPublication(
        const QString& title,
        const QString& description,
        bool is_favorite,
        const std::optional<QDate>& release_date,
        const QStringList authors,
        const QString& publisher,
        unsigned int page_number,
        const QUuid& uuid
    ):
        AbstractArticle(
            title,
            description,
            is_favorite,
            release_date,
            uuid
        ),
        _authors(authors),
        _publisher(publisher),
        _page_number(page_number)
    {}

    const QStringList& AbstractPublication::getAuthors() const {
        return _authors;
    }

    void AbstractPublication::setAuthors(const QStringList& author_list) {
        _authors = author_list;
    }

    const QString& AbstractPublication::getPublisher() const {
        return _publisher;
    }
    void AbstractPublication::setPublisher(const QString& publisher) {
        _publisher = publisher;
    }

    unsigned int AbstractPublication::getPageNumber() const {
        return _page_number;
    }
    void AbstractPublication::setPageNumber(unsigned int page_number) {
        _page_number = page_number;
    }

};
