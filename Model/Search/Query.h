#ifndef QUERY_H
#define QUERY_H

#include <QString>

namespace Model::Search {

class Query {
public:

private:
    bool _is_book;
    bool _is_movie;
    bool _is_issue;
    bool _is_favorite;
    QString _text;

public:
    Query(QString text, bool is_book, bool is_movie, bool is_issue, bool is_favorite):
        _is_book{is_book},
        _is_movie{is_movie},
        _is_issue{is_issue},
        _is_favorite{is_favorite},
        _text{text}
    {}

    bool isBook() const;
    bool isMovie() const;
    bool isIssue() const;
    bool isFavorite() const;
    QString getText() const;

};

}
#endif // QUERY_H
