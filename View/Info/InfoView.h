#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QWeakPointer>
#include <QWidget>
#include <QStackedLayout>

#include "Model/AbstractArticle.h"
#include "Model/Library.h"

#include "View/Info/Editor/EditInfoBase.h"
#include "View/Info/Editor/EditPageContainer.h"
#include "View/Info/InfoPageContainer.h"
#include "View/Info/NewArticlePage.h"

class InfoView : public QWidget
{
    Q_OBJECT

private:

    QWeakPointer<Model::AbstractArticle> shown_article;

    QStackedLayout *_stack;
    EditPageContainer *_edit_container;
    InfoPageContainer *_info_container;
    NewArticlePage *_new_article_page;

    void buildInfoPage(QWeakPointer<const Model::AbstractArticle>); //const Model::AbstractArticle& article);
    void buildEditor(QWeakPointer<const Model::AbstractArticle>); //const Model::AbstractArticle& article);

    /// @brief Costruisce le sotto pagine per mostrare un nuovo articolo
    void buildPage(QWeakPointer<Model::AbstractArticle>); //QWeakPointer<Model::AbstractArticle> new_article);

    /// @brief Mostra la pagina informazioni
    void showArticleInfoDirectly();

    /// @brief Mostra la pagina di editing
    void showArticleEditorDirectly();

    /// @brief Mostra la pagina informazioni
    void showArticleInfo(QWeakPointer<Model::AbstractArticle>);

    /// @brief Mostra la pagina di editing
    void showArticleEditor(QWeakPointer<Model::AbstractArticle>);

    /// @brief Mostra il form per creare un nuovo articolo
    void showNewArticleForm();

public:
    explicit InfoView(QWidget *parent = nullptr);

    QWeakPointer<Model::AbstractArticle> getShownArticle() const;

signals:
    // Richieste
    void requestAddArticle(Model::AbstractArticle*); // -> MainWindow
    void requestEditCancel();
    void requestEditArticle(QWeakPointer<Model::AbstractArticle>, QPointer<EditInfoBase>);  // -> MainWindow
    void requestFavoriteArticle(QWeakPointer<Model::AbstractArticle>); // -> MainWindow

    // Risultati: li invio solo se un'azione è andata a buon fine
    void resultDeleteArticle(QWeakPointer<Model::AbstractArticle>);     // -> MainWindow
    void resultEditArticle(QWeakPointer<Model::AbstractArticle>);       // -> MainWindow
    void resultOpenEditor(QWeakPointer<Model::AbstractArticle>);        // -> MainWindow, SelectView
    void resultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);   // -> InfoBase
    void resultShowArticle(QWeakPointer<Model::AbstractArticle>);       // -> MainWindow, SelectView
    void resultUpdateArticle(QWeakPointer<Model::AbstractArticle>);     // -> SelectView

    void resultDeleteCurrent();
    void resultOpenEditorCurrent();     // -> MainWindow, SelectView
    void resultOpenNewLibrary(std::optional<const QString>); // -> MainWindow

public slots:

    // Slot ricezione richieste
    void onRequestDeleteArticle(QWeakPointer<Model::AbstractArticle>);  // <- InfoView
    void onRequestDeleteCurrent();  // <- MainWindow
    void onRequestEditCurrent();    // <- EditInfoBase
    void onRequestShowArticle(QWeakPointer<Model::AbstractArticle>);
    void onRequestUpdateArticle(QWeakPointer<Model::AbstractArticle>);
    void onRequestOpenEditor(QWeakPointer<Model::AbstractArticle>);
    void onRequestOpenEditorCurrent();
    void onRequestNewArticle();
    void onRequestOpenNewLibrary(std::optional<const QString>);

    // Slot ricezione risultati
    void onResultAddArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultCancelEdit();  // <- EditInfoBase
    void onResultCancelNewArticle();  // <- NewArticlePage
    void onResultEditArticle(QWeakPointer<Model::AbstractArticle>); // <- MainWindow
    void onResultFavoriteArticle(QWeakPointer<Model::AbstractArticle>);
    void onResultLoadLibrary(Model::Library&);
};

#endif // INFOVIEW_H
