#ifndef INFOBASE_H
#define INFOBASE_H

#include <QFormLayout>
#include <QWeakPointer>
#include <QWidget>

#include "Model/AbstractArticle.h"

class InfoBase : public QWidget
{
    Q_OBJECT

private:
    QFormLayout *_form;

public:
    explicit InfoBase(const Model::AbstractArticle& article, QWidget *parent = nullptr);

    QFormLayout * mainLayout() const;

signals:
    // Segnale interno
    void changeFavoriteButtonState(bool);

    // Richieste
    void requestFavoriteCurrent();
    void requestOpenEditorCurrent();

public slots:
    // Risultati
    void onResultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
};

#endif // INFOBASE_H
