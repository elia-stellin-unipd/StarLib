#include "Query.h"

namespace Model::Search {
bool Query::isBook() const { return _is_book; }
bool Query::isMovie() const { return _is_movie; }
bool Query::isIssue() const { return _is_issue; }
bool Query::isFavorite() const { return _is_favorite; }

QString Query::getText() const  { return _text; }
}
