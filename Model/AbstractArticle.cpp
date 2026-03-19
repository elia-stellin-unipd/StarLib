#include "AbstractArticle.h"

namespace Model {

    AbstractArticle::AbstractArticle(
        const QString& title,
        const QString& description,
        bool is_favorite,
        const std::optional<QDate>& release_date,
        const QUuid& uuid
    ):
        _uuid(uuid),
        _title(title), 
        _description(description),
        _is_favorite(is_favorite),
        _release_date(release_date)
    {}

    void AbstractArticle::setUuid(const QUuid& uuid) {
        _uuid = uuid;
    }
    const QUuid& AbstractArticle::getUuid() const {
        return _uuid;
    }

    const QString& AbstractArticle::getTitle() const {
        return _title;
    }
    const QString& AbstractArticle::getDescription() const {
        return _description; 
    }
    bool AbstractArticle::isFavorite() const {
        return _is_favorite;
    }
    const std::optional<QDate>& AbstractArticle::getReleaseDate() const {
        return _release_date;
    }

    QString AbstractArticle::getFullName() const {
        return QString("\"%1\" (%2)").arg(getTitle(), getArticleDisplayType());
    }

    void AbstractArticle::setDescription(const QString& description) { _description = description; }
    void AbstractArticle::setTitle(const QString& title) { _title = title; }
    void AbstractArticle::setFavorite(bool flag) { _is_favorite = flag; }
    void AbstractArticle::setReleaseDate(QDate date) { _release_date = date; }
    void AbstractArticle::unsetReleaseDate() { _release_date = std::nullopt; }
    
    bool AbstractArticle::isReleaseDateSet() const {
        return _release_date != std::nullopt;
    }
};
