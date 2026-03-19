#ifndef NEWARTICLEPAGE_H
#define NEWARTICLEPAGE_H

#include <QFormLayout>
#include <QPointer>
#include <QStackedLayout>
#include <QWidget>

#include "Model/AbstractArticle.h"

class NewArticlePage : public QWidget
{
    Q_OBJECT
private:
    enum ArticleType {
        Book,
        Movie,
        Issue
    };

    QFormLayout *_book_form;
    QFormLayout *_issue_form;
    QFormLayout *_movie_form;
    //QFormLayout *_form_layout;

public:
    explicit NewArticlePage(QWidget *parent = nullptr);

    /// @brief Costruisce da capo i form
    void build();

signals:
    // Richieste
    void requestAddArticle(Model::AbstractArticle*);  // -> InfoView

    // Risultati
    void resultCancelNewArticle();  // -> InfoView

public slots:
    void onRequestCancelNewArticle(); // <- this
};

#endif // NEWARTICLEPAGE_H
