#include "ArticlePreviewBase.h"

#include "View/FavoriteButton.h"

#include "Utils/Style.h"

#include <QLabel>
#include <QMenu>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>
#include <QDebug>


using namespace Model;

ArticlePreviewBase::ArticlePreviewBase(
    QWeakPointer<Model::AbstractArticle> article,
    QWidget *parent
)
    : QFrame{parent}, _article(article)
{
    setStyleSheet(Utils::Style::load(":/assets/style/ArticlePreviewBase.qss"));
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(
        this, &QWidget::customContextMenuRequested,
        this, &ArticlePreviewBase::showContextMenu
    );

    _main_layout = new QGridLayout(this);

    FavoriteButton *favorite = new FavoriteButton(_article.toStrongRef()->isFavorite());
    _main_layout->addWidget(favorite, 0, 1);

    connect(
        favorite, &QPushButton::pressed,
        this, &ArticlePreviewBase::toggleFavorite
    );

    connect(
        this, &ArticlePreviewBase::changeFavoriteButton,
        favorite, &FavoriteButton::changeState
    );
}

void ArticlePreviewBase::toggleFavorite() {
    emit requestFavoriteArticle(_article);
}

void ArticlePreviewBase::showContextMenu(const QPoint& pos) {
    if (_article.isNull()) {
        return;
    }
    auto shared = _article.toStrongRef();

    QMenu contextMenu("Menù per" + shared->getTitle(), this);
    contextMenu.setStyleSheet("background-color: #202020;");

    QAction action_favorite(shared->isFavorite()? "Rimuovi dai preferiti" : "Aggiungi ai preferiti", this);
    connect(&action_favorite, &QAction::triggered, this, &ArticlePreviewBase::toggleFavorite);
    contextMenu.addAction(&action_favorite);

    QAction action_edit("Modifica elemento", this);
    connect(&action_edit, &QAction::triggered, [=]{
        emit requestOpenEditor(_article);
    });
    contextMenu.addAction(&action_edit);

    QAction action_remove("Elimina elemento", this);

    connect(&action_remove, &QAction::triggered, [=]{ emit requestDeleteArticle(_article);});
    /// @note: quando mi arriva il risultato => ho la conferma di cancellazione, allora mando
    /// removeWidget(this);
    contextMenu.addAction(&action_remove);

    shared.clear();
    contextMenu.exec(mapToGlobal(pos));
}

void ArticlePreviewBase::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        emit requestShowArticle(_article); //emit showArticle(_article);
    }
}

// QVBoxLayout* ArticlePreviewBase::mainLayout() const {
QGridLayout* ArticlePreviewBase::mainLayout() const {
    return _main_layout;
}

const QWeakPointer<AbstractArticle> ArticlePreviewBase::getArticle() const {
    return _article;
}

void ArticlePreviewBase::onResultFavoriteArticle(QWeakPointer<Model::AbstractArticle> article) {
    if (article == _article) {
        emit changeFavoriteButton(article.toStrongRef()->isFavorite());
    }
}

