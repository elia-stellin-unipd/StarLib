#include "Library.h"

#include <QDebug>
#include <QScopedPointer>

namespace Model {


    Library::Library(
        const QString& name,
        const QList<QSharedPointer<AbstractArticle>>& articles
    ): _name(name), _articles(articles)
    {}

    const QList<QSharedPointer<AbstractArticle>>& Library::getArticles() const {
        return _articles;
    }

    QWeakPointer<AbstractArticle> Library::addArticle(AbstractArticle *article) {
        QSharedPointer<AbstractArticle> shared_article(article);
        _articles.push_back(shared_article);
        return shared_article.toWeakRef();
    }

    void Library::deleteArticle(QWeakPointer<AbstractArticle> article) {
        int index = _articles.indexOf(article.toStrongRef());
        QSharedPointer<AbstractArticle> taken = _articles.takeAt(index);
    }

    void Library::clear() {
        _articles.clear();
        setName("");
    }

    const QString& Library::getName() const { return _name; }
    qsizetype Library::getCount() const { return _articles.count(); }

    void Library::setName(const QString& name) {
        _name = name;
    }


}
