#include "ResultGridWidget.h"

#include <QScrollArea>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QVector>

#include "Model/AbstractArticle.h"

#include "View/Select/ArticlePreviewBase.h"
#include "View/Select/NewArticleButton.h"

#include "Visitors/ArticlePreviewWidget.h"
#include "Visitors/QueryMatchVisitor.h"

#include "Utils/Layout.h"

using namespace Model;

ResultGridWidget::ResultGridWidget(QWidget *parent)
    : QWidget{parent}, _last_selected{nullptr}, _layout{new View::Layouts::FlowLayout(this)}
{
    _layout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
}

void ResultGridWidget::loadLibrary(Library& library) {
    _last_selected = nullptr;

    Utils::Layout::clear(_layout);

    // Aggiunge il bottone
    NewArticleButton *new_button = new NewArticleButton();
    connect(
        new_button, &QPushButton::pressed,
        this, &ResultGridWidget::requestNewArticle
    );
    _layout->addWidget(new_button);

    // Importante! Ripulisce la lookup table e permette alla ricerca di funzionare
    _widget_lookup_table.clear();

    // Aggiunge i vari articoli alla griglia
    for (QSharedPointer<AbstractArticle> article : library.getArticles()) {
        addArticlePreview(article.toWeakRef());
    }
}

ArticlePreviewBase *ResultGridWidget::addArticlePreview(QWeakPointer<Model::AbstractArticle> article, int index) {
    using namespace Visitors;

    ArticlePreviewWidget *visitor = new ArticlePreviewWidget(article);
    article.toStrongRef()->accept(visitor);
    ArticlePreviewBase *widget = visitor->getWidget();

    if (index <= -1) {
        _layout->addWidget(widget);
    }
    else {
        _layout->insertWidget(index + 1, widget); // Il primo elemento è sempre il bottone new
    }
    _layout->update();
    // Inserisci nella tabella per lookup veloce quando elimino o modifico un widget
    _widget_lookup_table.insert(article.toStrongRef().get(), widget);

    // Richieste (ArticlePreviewBase -> ResultGridWidget)
    connect(
        widget, &ArticlePreviewBase::requestDeleteArticle,
        this, &ResultGridWidget::requestDeleteArticle
    );
    connect(
        widget, &ArticlePreviewBase::requestOpenEditor,
        this, &ResultGridWidget::requestOpenEditor
    );
    connect(
        widget, &ArticlePreviewBase::requestFavoriteArticle,
        this, &ResultGridWidget::requestFavoriteArticle
    );
    connect(
        widget, &ArticlePreviewBase::requestShowArticle,
        this, &ResultGridWidget::requestShowArticle
    );
    connect(
        widget, &ArticlePreviewBase::requestUpdateArticle,
        this, &ResultGridWidget::requestUpdateArticle
    );

    // Risultati (ResultGridWidget -> ArticlePreviewBase)
    connect(
        this, &ResultGridWidget::resultFavoriteArticle,
        widget, &ArticlePreviewBase::onResultFavoriteArticle
    );

    return widget;
}

// SLOTS ///////////////////////////////////////////////////////////////////////////////////////////
void ResultGridWidget::onRemoveWidget(ArticlePreviewBase *widget) {
    if (_last_selected == widget) {
        _last_selected = nullptr;
    }

    if (widget) {
        widget->deleteLater();
        // emit deleteArticle(widget->getArticle());
    }
}

void ResultGridWidget::onSelectWidget(ArticlePreviewBase *widget) {
    if (widget == _last_selected) { return; }

    if (_last_selected) {
        _last_selected->setProperty("selected", false);
        style()->polish(_last_selected);
    }
    widget->setProperty("selected", true);
    style()->polish(widget);

    _last_selected = widget;
}

void ResultGridWidget::onSearchQuery(Model::Search::Query query) {
    using namespace Visitors;

    int visible_index = 0;
    for (
        auto i = _widget_lookup_table.cbegin(),
            end = _widget_lookup_table.cend();
        i != end;
        ++i
    ) {
        AbstractArticle *article = i.key();
        if (!article) { continue; }

        ArticlePreviewBase *apb = i.value();
        if (!apb) { continue; }

        QueryMatchVisitor visitor = QueryMatchVisitor(query);
        article->accept(&visitor);

        // Mostra
        if (visitor.getMatch()) {
            _layout->removeWidget(apb);
            _layout->insertWidget(visible_index + 1, apb);
            apb->setHidden(false);

            visible_index++;
        }
        // Nascondi (ovvero imposta hidden e metti alla fine per evitare problemi di spacing)
        else {
            _layout->takeAt(_layout->indexOf(apb));
            _layout->addWidget(apb);
            apb->setHidden(true);
            // Imposta alla fine
        }
    }
}

// Risultati ////////////////////////////////////////////////////////////////////////////
void ResultGridWidget::onResultAddArticle(QWeakPointer<AbstractArticle> article) {
    if (article.isNull()) {
        return;
    }

    // -1 perché aggiungo in fondo
    onSelectWidget(addArticlePreview(article, -1));
}

void ResultGridWidget::onResultDeleteArticle(AbstractArticle* article) {
    if (_widget_lookup_table.contains(article)) {
        ArticlePreviewBase *widget = _widget_lookup_table.take(article);
        if (widget) {
            widget->deleteLater();
        }
    }
}

void ResultGridWidget::onResultEditArticle(QWeakPointer<AbstractArticle> article) {
    onResultUpdateArticle(article);
}


void ResultGridWidget::onResultShowArticle(QWeakPointer<AbstractArticle> article) {
    ArticlePreviewBase *widget = _widget_lookup_table.value(article.toStrongRef().get(), nullptr);

    if (widget == _last_selected) {
        return;
    }

    if (!_last_selected.isNull()) {
        _last_selected->setProperty("selected", false);
        style()->polish(_last_selected);
    }
    widget->setProperty("selected", true);
    style()->polish(widget);

    _last_selected = widget;
}

void ResultGridWidget::onResultUpdateArticle(QWeakPointer<AbstractArticle> article) {
    if (article.isNull()) {
        return;
    }

    QSharedPointer<AbstractArticle> shared(article.toStrongRef());

    if (!_widget_lookup_table.contains(shared.get())) {
        return;
    }

    ArticlePreviewBase *old_widget = _widget_lookup_table.value(shared.get());
    int old_widget_index = _layout->indexOf(old_widget);

    // NOTA: addArticlePreview inserisce la entry nella LUT
    ArticlePreviewBase *new_widget = addArticlePreview(article, old_widget_index);
    _layout->removeWidget(old_widget);
    old_widget->deleteLater(); // NOTA: questo è importante!

    onSelectWidget(new_widget);
}

void ResultGridWidget::onResultNewArticle() {}

void ResultGridWidget::onResultLoadLibrary(Library& library) {
    loadLibrary(library);
}
