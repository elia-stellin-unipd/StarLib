#ifndef SELECTVIEW_H
#define SELECTVIEW_H

#include <QWidget>

#include "Model/Library.h"

class SelectView : public QWidget
{
    Q_OBJECT
public:
    explicit SelectView(QWidget *parent = nullptr);

signals:
    void setSearchBarFocus();

    // Richieste
    void requestDeleteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void requestFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestShowArticle(QWeakPointer<Model::AbstractArticle>);
    void requestUpdateArticle(QWeakPointer<Model::AbstractArticle>);
    void requestNewArticle();

    // Risultati
    void resultAddArticle(QWeakPointer<Model::AbstractArticle>);
    void resultDeleteArticle(Model::AbstractArticle*);
    void resultEditArticle(QWeakPointer<Model::AbstractArticle>);
    void resultOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void resultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void resultShowArticle(QWeakPointer<Model::AbstractArticle>);
    void resultUpdateArticle(QWeakPointer<Model::AbstractArticle>);
    void resultNewArticle();
    void resultLoadLibrary(Model::Library&);
};

#endif // SELECTVIEW_H
