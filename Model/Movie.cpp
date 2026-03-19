#include "Movie.h"

namespace Model {
    using namespace Helper;

    QString Movie::getArticleDisplayType() const  {
        return QString("Film");
    }

    const QString Movie::ARTICLE_TYPE("movie");
    QString Movie::getArticleType() const {
        return ARTICLE_TYPE;
    }

    Movie::Movie(
        const QString& title,
        const QString& description,
        bool is_favorite,
        const std::optional<QDate>& release_date,
        const QString& director,
        const MediaRuntime& length,
        const QUuid& uuid
    ):
        AbstractArticle(
            title,
            description,
            is_favorite,
            release_date,
            uuid
        ),
        _director(director),
        _length(length)
    {}

    const QString& Movie::getDirector() const { return _director; }
    void Movie::setDirector(const QString& director) { _director = director; }

    const MediaRuntime& Movie::getLength() const { return _length; }
    void Movie::setLength(const MediaRuntime& length) { _length = length;}

    void Movie::accept(Visitors::ArticleConstVisitor *visitor) const {
        visitor->visit(*this);
    }

    void Movie::accept(Visitors::ArticleVisitor *visitor) {
        visitor->visit(*this);
    }
}
