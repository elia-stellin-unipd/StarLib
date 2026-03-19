#ifndef MOVIE_H
#define MOVIE_H

#include "AbstractArticle.h"
#include "MediaRuntime.h"

namespace Model {
    class Movie: public AbstractArticle {
    private:
        QString _director;
        Helper::MediaRuntime _length;
    public:
        QString getArticleDisplayType() const override;
        QString getArticleType() const override;
        static const QString ARTICLE_TYPE;

        Movie(
            const QString& title = "",
            const QString& description = "",
            bool is_favorite = false,
            const std::optional<QDate>& release_date = std::nullopt,
            const QString& director = "",
            const Helper::MediaRuntime& length = Helper::MediaRuntime(),
            const QUuid& uuid = QUuid::createUuid()
        );

        const QString& getDirector() const;
        void setDirector(const QString& director);
        const Helper::MediaRuntime& getLength() const;
        void setLength(const Helper::MediaRuntime& length);
    
        void accept(Visitors::ArticleConstVisitor *visitor) const override;
        void accept(Visitors::ArticleVisitor *visitor) override;
    };
};

#endif
