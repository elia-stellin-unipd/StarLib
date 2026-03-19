#ifndef ARTICLEPREVIEWBASE_H
#define ARTICLEPREVIEWBASE_H

#include <QFrame>
#include <QVBoxLayout>
#include <QWeakPointer>
#include <QGridLayout>

#include "Model/AbstractArticle.h"
#include "Model/Library.h"

class ArticlePreviewBase : public QFrame
{
    Q_OBJECT

private:

    QWeakPointer<Model::AbstractArticle> _article;
    QGridLayout *_main_layout;

public:
    /// ho modificato qui
    explicit ArticlePreviewBase(
        QWeakPointer<Model::AbstractArticle> article,
        QWidget *parent = nullptr
    );

    void mousePressEvent(QMouseEvent *event) override;

    QGridLayout* mainLayout() const;

    const QWeakPointer<Model::AbstractArticle> getArticle() const;

signals:
    void changeFavoriteButton(bool);

    void updateArticle(QWeakPointer<Model::AbstractArticle>);
    void showArticle(QWeakPointer<Model::AbstractArticle>);

    // Verso ResultGridWidget
    void removeWidget(ArticlePreviewBase *);
    void selectWidget(ArticlePreviewBase *);

    // Richieste: vengono inviate da ArticlePreviewBase, mentre ResultGridWidget ne prende le risposte
    void requestDeleteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void requestFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestShowArticle(QWeakPointer<Model::AbstractArticle>);
    void requestUpdateArticle(QWeakPointer<Model::AbstractArticle>);

public slots:
    void showContextMenu(const QPoint&);
    void toggleFavorite();

    void onResultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
};

#endif // ARTICLEPREVIEWBASE_H
