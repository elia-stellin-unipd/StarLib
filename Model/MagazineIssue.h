#ifndef MAGAZINEISSUE_H
#define MAGAZINEISSUE_H

#include "AbstractPublication.h"

namespace Model {

    class MagazineIssue: public AbstractPublication {
        
    private:
        QString _ISSN;
        unsigned int _issue_number;
    
    public:
        QString getArticleDisplayType() const override;
        QString getArticleType() const override;
        static const QString ARTICLE_TYPE;

        MagazineIssue(
            const QString& title = "",
            const QString& description = "",
            bool is_favorite = false,
            const std::optional<QDate>& release_date = std::nullopt,
            const QStringList& authors = {},
            const QString& publisher = "",
            unsigned int page_number = 0,
            const QString& ISSN = "",
            unsigned int issue_number = 0,
            const QUuid& uuid = QUuid::createUuid()
        );

        const QString& getISSN() const;
        void setISSN(const QString& ISSN);
        unsigned int getIssueNumber() const;
        void setIssueNumber(unsigned int);

        void accept(Visitors::ArticleConstVisitor *visitor) const override;
        void accept(Visitors::ArticleVisitor *visitor) override;
    };
}

#endif
