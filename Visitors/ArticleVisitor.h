#ifndef ARTICLEVISITOR_H
#define ARTICLEVISITOR_H

// Forward declaration per evitare inclusioni circolari
namespace Model {
    class Book;
    class Movie;
    class MagazineIssue;
};

namespace Visitors {
    
    class ArticleVisitor {
    public:
        virtual ~ArticleVisitor() {}
        virtual void visit(Model::Book &book) = 0;
        virtual void visit(Model::Movie &movie) = 0;
        virtual void visit(Model::MagazineIssue &magazine) = 0;
    };
};
#endif
