#include "QueryMatchVisitor.h"

namespace Visitors {


bool QueryMatchVisitor::commonMatch(const Model::AbstractArticle& article) {
    return article.getTitle().contains(query.getText(), Qt::CaseInsensitive)
           && (query.isFavorite()? article.isFavorite() : true);
}

void QueryMatchVisitor::visit(const Model::Book& book) {
    match = query.isBook() && commonMatch(book);
}

void QueryMatchVisitor::visit(const Model::MagazineIssue& issue) {
    match = query.isIssue() && commonMatch(issue);
}

void QueryMatchVisitor::visit(const Model::Movie& movie) {
    match = query.isMovie() && commonMatch(movie);
}

bool QueryMatchVisitor::getMatch() const {
    return match;
}

}
