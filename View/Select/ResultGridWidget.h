#ifndef RESULTGRIDWIDGET_H
#define RESULTGRIDWIDGET_H

#include <QResizeEvent>
#include <QMap>
#include <QSharedPointer>
#include <QWidget>

#include "Model/Library.h"

#include "View/Layouts/FlowLayout.h"
#include "View/Select/ArticlePreviewBase.h"

#include "Model/Search/Query.h"

class ResultGridWidget : public QWidget
{
    Q_OBJECT

private:
    QPointer<ArticlePreviewBase> _last_selected;
    View::Layouts::FlowLayout *_layout;

    /// @brief Una mappa di lookup veloce che permette di trovare qualunque widget all'interno della griglia
    /// tramite l'articolo che esso rappresenta.
    /// Utilizzato per trovare velocemente un widget da mostrare o da eliminare, avendone solamente l'articolo associato
    QMap<Model::AbstractArticle*, ArticlePreviewBase*> _widget_lookup_table;

    /// @brief Inserisci la preview di un certo elemento a indice index (relativo all'ordine degli elementi,
    /// senza contare il bottone New).
    /// @return il puntatore all'ArticlePreviewBase creato dalla funzione
    ArticlePreviewBase* addArticlePreview(QWeakPointer<Model::AbstractArticle> article, int index = -1);

    /// @brief Carica una libreria nuova
    void loadLibrary(Model::Library& library);

public:
    explicit ResultGridWidget(QWidget *parent = nullptr);

signals:
    void deleteArticle(QWeakPointer<Model::AbstractArticle>);
    void updateArticle(QWeakPointer<Model::AbstractArticle>);
    void showArticle(QWeakPointer<Model::AbstractArticle>);

    // Richieste
    void requestDeleteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void requestFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void requestShowArticle(QWeakPointer<Model::AbstractArticle>);
    void requestUpdateArticle(QWeakPointer<Model::AbstractArticle>);
    void requestNewArticle();

    // Risultati
    void resultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);

public slots:

    /// @brief Slot chiamato per rimuovere un widget di preview dalla griglia
    void onRemoveWidget(ArticlePreviewBase *);

    /// @brief Slot chiamato per selezionare un widget di preview nella griglia
    void onSelectWidget(ArticlePreviewBase *);

    void onSearchQuery(Model::Search::Query);

    // Risultati
    void onResultAddArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultDeleteArticle(Model::AbstractArticle*);
    void onResultEditArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultShowArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultUpdateArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultNewArticle();
    void onResultLoadLibrary(Model::Library&);
};

#endif // RESULTGRIDWIDGET_H
