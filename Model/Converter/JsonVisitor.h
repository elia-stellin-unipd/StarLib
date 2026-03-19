#ifndef JSONVISITOR_H
#define JSONVISITOR_H

#include <QJsonObject>

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

#include "Visitors/ArticleConstVisitor.h"

namespace Model::Converter {
    class JsonVisitor: public Visitors::ArticleConstVisitor {
    private:
        QJsonObject json_object;

        void convertBase(const Model::AbstractArticle& article);
        void convertPublication(const Model::AbstractPublication& publication);
    public:
        QJsonObject getObject() const;

        void visit(const Model::Book& book);
        void visit(const Model::MagazineIssue& issue);
        void visit(const Model::Movie& movie);
    };
}

#endif // JSONVISITOR_H
