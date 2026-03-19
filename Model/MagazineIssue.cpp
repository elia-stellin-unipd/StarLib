#include "MagazineIssue.h"

namespace Model {

    QString MagazineIssue::getArticleDisplayType() const {
        return QString("Uscita di rivista");
    }
    
    const QString MagazineIssue::ARTICLE_TYPE("issue");
    QString MagazineIssue::getArticleType() const {
        return ARTICLE_TYPE;
    }

    MagazineIssue::MagazineIssue(
        const QString& title,
        const QString& description,
        bool is_favorite,
        const std::optional<QDate>& release_date,
        const QStringList& authors,
        const QString& publisher,
        unsigned int page_number,
        const QString& ISSN,
        unsigned int issue_number,
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
        _ISSN(ISSN),
        _issue_number(issue_number)
    {}

    const QString& MagazineIssue::getISSN() const {
        return _ISSN;
    }
    void MagazineIssue::setISSN(const QString& ISSN) {
        _ISSN = ISSN;
    }
    unsigned int MagazineIssue::getIssueNumber() const {
        return _issue_number;
    }
    void MagazineIssue::setIssueNumber(unsigned int issue_number) { 
        _issue_number = issue_number; 
    }

    void MagazineIssue::accept(Visitors::ArticleConstVisitor *visitor) const {
        visitor->visit(*this);
    }

    void MagazineIssue::accept(Visitors::ArticleVisitor *visitor) {
        visitor->visit(*this);
    }
}
