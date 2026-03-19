#include "SelectView.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QStyle>
#include <QPushButton>
#include <QIcon>


#include "SearchBarWidget.h"
#include "ResultGridWidget.h"

using namespace Model;

SelectView::SelectView( QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    SearchBarWidget *search_bar = new SearchBarWidget();
    layout->addWidget(search_bar);

    QScrollArea *scroll_area = new QScrollArea();
    scroll_area->setContentsMargins(0, 0, 0, 0);
    scroll_area->setStyleSheet(
        "border-radius: 4px;"
        "margin: 0px;"
    );

    ResultGridWidget *grid_widget = new ResultGridWidget();

    // SelectView -> SearchBarWidget
    connect(
        this, &SelectView::setSearchBarFocus,
        search_bar, &SearchBarWidget::setFocus
    );

    // SearchBarWidget -> ResultGridWidget
    connect(
        search_bar, &SearchBarWidget::searchQuery,
        grid_widget, &ResultGridWidget::onSearchQuery
    );

    // Richieste (ResultGridWidget -> SelectView)
    connect(
        grid_widget, &ResultGridWidget::requestDeleteArticle,
        this, &SelectView::requestDeleteArticle
    );
    connect(
        grid_widget, &ResultGridWidget::requestOpenEditor,
        this, &SelectView::requestOpenEditor
    );
    connect(
        grid_widget, &ResultGridWidget::requestFavoriteArticle,
        this, &SelectView::requestFavoriteArticle
    );
    connect(
        grid_widget, &ResultGridWidget::requestNewArticle,
        this, &SelectView::requestNewArticle
    );
    connect(
        grid_widget, &ResultGridWidget::requestShowArticle,
        this, &SelectView::requestShowArticle
    );
    connect(
        grid_widget, &ResultGridWidget::requestUpdateArticle,
        this, &SelectView::requestUpdateArticle
    );

    // Risultati (SelectView -> ResultGridWidget)
    connect(
        this, &SelectView::resultAddArticle,
        grid_widget, &ResultGridWidget::onResultAddArticle
    );
    connect(
        this, &SelectView::resultDeleteArticle,
        grid_widget, &ResultGridWidget::onResultDeleteArticle
    );
    connect(
        this, &SelectView::resultEditArticle,
        grid_widget, &ResultGridWidget::onResultEditArticle
    );
    connect(
        this, &SelectView::resultFavoriteArticle,
        grid_widget, &ResultGridWidget::resultFavoriteArticle
    );
    connect(
        this, &SelectView::resultShowArticle,
        grid_widget, &ResultGridWidget::onResultShowArticle
    );
    connect(
        this, &SelectView::resultUpdateArticle,
        grid_widget, &ResultGridWidget::onResultUpdateArticle
    );
    connect(
        this, &SelectView::resultLoadLibrary,
        grid_widget, &ResultGridWidget::onResultLoadLibrary
    );

    scroll_area->setWidget(grid_widget);
    scroll_area->setWidgetResizable(true);
    layout->addWidget(scroll_area);
}
