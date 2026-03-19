#include "Book.h"

namespace Model {

    QString Book::getArticleDisplayType() const {
        return QString("Libro");
    }

    const QString Book::ARTICLE_TYPE("book");
    QString Book::getArticleType() const {
        return ARTICLE_TYPE;
    }


    Book::Book(
        const QString& title,
        const QString& description,
        bool is_favorite,
        const std::optional<QDate>& release_date,
        const QStringList& authors,
        const QString& publisher,
        unsigned int page_number,
        const QString& ISBN,
        const QUuid& uuid
    ): 
        AbstractPublication(
            title,
            description,
            is_favorite,
            release_date,
            authors,
            publisher,
            page_number,
            uuid
        ),
        _ISBN(ISBN)
    {}

    const QString& Book::getISBN() const { return _ISBN; }
    void Book::setISBN(const QString& ISBN) { _ISBN = ISBN; }

    void Book::accept(Visitors::ArticleConstVisitor *visitor) const {
        visitor->visit(*this);
    }

    void Book::accept(Visitors::ArticleVisitor *visitor) {
        visitor->visit(*this);
    }
};
