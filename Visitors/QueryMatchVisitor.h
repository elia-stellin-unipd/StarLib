#ifndef QUERYMATCHVISITOR_H
#define QUERYMATCHVISITOR_H

#include "Model/Book.h"
#include "Model/MagazineIssue.h"
#include "Model/Movie.h"

#include "Model/Search/Query.h"

#include "Visitors/ArticleConstVisitor.h"

namespace Visitors {

class QueryMatchVisitor : public ArticleConstVisitor
{
private:
    bool match;
    const Model::Search::Query& query;

    bool commonMatch(const Model::AbstractArticle&);

public:
    QueryMatchVisitor(const Model::Search::Query& q): match{false}, query{q} {}

    void visit(const Model::Book&);
    void visit(const Model::MagazineIssue&);
    void visit(const Model::Movie&);

    bool getMatch() const;
};

}
#endif // QUERYMATCHVISITOR_H
