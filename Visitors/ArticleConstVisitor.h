#ifndef ARTICLECONSTVISITOR_H
#define ARTICLECONSTVISITOR_H

// Forward declaration
namespace Model {
class Book;
class Movie;
class MagazineIssue;
};

namespace Visitors {

class ArticleConstVisitor {
public:
    virtual ~ArticleConstVisitor() {}
    virtual void visit (const Model::Book& book) = 0;
    virtual void visit (const Model::Movie& movie) = 0;
    virtual void visit (const Model::MagazineIssue& magazine) = 0;
};
};

#endif // ARTICLECONSTVISITOR_H
