#include "InfoView.h"

#include <QDebug>
#include <QFrame>
#include <QPointer>
#include <QLabel>
#include <QMessageBox>
#include <QScrollArea>
#include <QStackedLayout>
#include <QTextEdit>
#include <QVBoxLayout>

#include "Utils/Style.h"

#include "View/Dialog/ConfirmDialogBox.h"
#include "Visitors/ArticleInfoWidget.h"
#include "Visitors/ArticleEditInfoWidget.h"

using namespace Model;
using namespace Visitors;
using namespace Utils;


InfoView::InfoView(QWidget *parent)
    : QWidget{parent},
    shown_article(nullptr),
    _edit_container{new EditPageContainer(this)},
    _info_container{new InfoPageContainer(this)},
    _new_article_page{new NewArticlePage(this)}
{
    setStyleSheet(Style::load(":/assets/style/InfoView.qss"));

    QVBoxLayout *layout = new QVBoxLayout(this);

        QScrollArea *scroll_area = new QScrollArea();
        scroll_area->setWidgetResizable(true);

        _stack = new QStackedLayout();
        _stack->addWidget(_info_container);
        _stack->addWidget(_edit_container);
        _stack->addWidget(_new_article_page);
        _stack->setCurrentWidget(_info_container);
        scroll_area->setLayout(_stack);

    layout->addWidget(scroll_area);

    connect(
        _new_article_page, &NewArticlePage::resultCancelNewArticle,
        this, &InfoView::onResultCancelNewArticle
    );

    connect(
        _new_article_page, &NewArticlePage::requestAddArticle,
        this, &InfoView::requestAddArticle
    );
}

QWeakPointer<Model::AbstractArticle> InfoView::getShownArticle() const {
    return shown_article;
}

void InfoView::buildInfoPage(QWeakPointer<const AbstractArticle> article) {

    if (article.isNull()) { return; }

    ArticleInfoWidget info_visitor;
    article.toStrongRef()->accept(&info_visitor);
    InfoBase *info_base = qobject_cast<InfoBase*>(info_visitor.getWidget());
    _info_container->setWidget(info_base);

    if (!info_base) {
        qWarning("InfoBase not found inside ArticleInfoWidget");
    }
    else {
        connect(
            info_base, &InfoBase::requestOpenEditorCurrent,
            this, &InfoView::onRequestOpenEditorCurrent
        );

        connect(
            info_base, &InfoBase::requestFavoriteCurrent,
            [=]{ emit requestFavoriteArticle(shown_article); }
        );

        connect(
            this, &InfoView::resultFavoriteArticle,
            info_base, &InfoBase::onResultFavoriteArticle
        );
    }
}

void InfoView::buildEditor(QWeakPointer<const AbstractArticle> article) {

    if (article.isNull()) { return; }

    ArticleEditInfoWidget edit_visitor;
    article.toStrongRef()->accept(&edit_visitor);
    EditInfoBase *edit_info = edit_visitor.getWidget();
    _edit_container->clearWidget();
    _edit_container->setWidget(edit_info);

    if (!edit_info) {
        qWarning("EditInfoBase not found inside ArticleEditInfoWidget!");
    }
    else {

        // Richieste (EditInfo -> InfoView)
        connect(
            edit_info, &EditInfoBase::requestEditCurrent,
            [=](QPointer<EditInfoBase> form) { requestEditArticle(shown_article, form); }
        );

        // Richieste (InfoView -> EditInfo)
        connect(
            this, &InfoView::requestEditCancel,
            edit_info, &EditInfoBase::onRequestCancelEdit
        );

        // Risultati (EditInfo -> InfoView)
        connect(
            edit_info, &EditInfoBase::resultCancelEdit,
            this, &InfoView::onResultCancelEdit
        );

    }
}

void InfoView::buildPage(QWeakPointer<AbstractArticle> new_article) {
    // new_article != shown_article
    buildInfoPage(new_article);
    buildEditor(new_article);
    _new_article_page->build();
}


void InfoView::showArticleInfoDirectly() {
    _stack->setCurrentWidget(_info_container);
}
void InfoView::showArticleEditorDirectly() {
    _stack->setCurrentWidget(_edit_container);
}


void InfoView::showArticleInfo(QWeakPointer<AbstractArticle> new_article) {
    if (new_article.isNull()) {
        _edit_container->clearWidget();
        _info_container->clearWidget();
        return;
    }

    QWidget *current = _stack->currentWidget();

    if (current == _info_container) {
        if (new_article == shown_article) {
            // non fare niente
            return;
        }
    }

    else if (current == _edit_container) {
        EditInfoBase *edit_info = _edit_container->getWidget();
        if (edit_info && edit_info->wasEdited()) {
            ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare le modifiche?");
            if (!confirm.ask()) { return; }
        }
    }

    else if (current == _new_article_page) {
        ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare la creazione?");
        if (!confirm.ask()) { return; }
    }

    if (new_article != shown_article) {
        buildPage(new_article);
        emit resultShowArticle(new_article);
    }
    _stack->setCurrentWidget(_info_container);
    shown_article = new_article;

}
void InfoView::showArticleEditor(QWeakPointer<AbstractArticle> new_article) {
    if (new_article.isNull()) {
        _edit_container->clearWidget();
        _info_container->clearWidget();
        return;
    }

    QWidget *current = _stack->currentWidget();

    if (current == _info_container) {
        if (new_article != shown_article) {
            buildPage(new_article);
            emit resultShowArticle(new_article);
        }

        emit resultOpenEditor(new_article);
        _stack->setCurrentWidget(_edit_container);
    }
    else if (current == _edit_container) {
        if (new_article == shown_article) {
            return;
        }

        // new_article != shown_article
        EditInfoBase *edit_info = _edit_container->getWidget();
        if (edit_info && edit_info->wasEdited()) {
            ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare le modifiche?");

            if (!confirm.ask()) { return; }
        }

        buildPage(new_article);
        emit resultShowArticle(new_article);
        emit resultOpenEditor(new_article);
    }
    else if (current == _new_article_page) {
        ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare la creazione?");

        if (!confirm.ask()) { return; }
    }

    shown_article = new_article;
}
void InfoView::showNewArticleForm() {
    QWidget *current = _stack->currentWidget();

    if (current == _edit_container) {
        EditInfoBase *edit_info = _edit_container->getWidget();
        if (edit_info && edit_info->wasEdited()) {
            ConfirmDialogBox confirm = ConfirmDialogBox("Sei sicuro di voler annullare le modifiche?");

            if (!confirm.ask()) { return; }
        }
    }

    _stack->setCurrentWidget(_new_article_page);

}

// Richieste ////////////////////////////////////////////////////////////////
void InfoView::onRequestDeleteArticle(QWeakPointer<AbstractArticle> article) {
    if (article.isNull()) {
        return;
    }

    bool confirm_delete = ConfirmDialogBox(
        QString("Sei sicuro di voler eliminare \"%1\"?").arg(article.toStrongRef()->getTitle()),
        QMessageBox::Warning
    ).ask();

    if (confirm_delete) {
        if (article == shown_article) {
            _edit_container->clearWidget();
            _info_container->clearWidget();
        }

        emit resultDeleteArticle(article);
    }
}

void InfoView::onRequestDeleteCurrent() {
    onRequestDeleteArticle(shown_article);
}

void InfoView::onRequestEditCurrent() {
    // Modifica effettivamente l'articolo qui col visitor
    emit resultEditArticle(shown_article);
}

void InfoView::onRequestNewArticle() {
    showNewArticleForm();
}

void InfoView::onRequestOpenEditor(QWeakPointer<AbstractArticle> article) {
    showArticleEditor(article);
}
void InfoView::onRequestOpenEditorCurrent() {
    onRequestOpenEditor(shown_article);
}

void InfoView::onRequestShowArticle(QWeakPointer<AbstractArticle> article) {
    showArticleInfo(article);
}

void InfoView::onRequestUpdateArticle(QWeakPointer<AbstractArticle> article) {
    if (article == shown_article && !article.isNull()) {
        buildPage(article);
    }
}

void InfoView::onRequestOpenNewLibrary(std::optional<const QString> path) {
    QWidget *current = _stack->currentWidget();

    if (current == _edit_container) {
        EditInfoBase *info_base = _edit_container->getWidget();

        if (info_base && info_base->wasEdited()) {
            ConfirmDialogBox confirm("Sei sicuro di voler annullare le modifiche?");

            if (!confirm.ask()) { return; }
            onResultCancelEdit();
        }
    }
    else if (current == _new_article_page) {
        ConfirmDialogBox confirm("Sei sicuro di voler annullare la creazione?");
        if (!confirm.ask()) { return; }
        onResultCancelNewArticle();
    }

    emit resultOpenNewLibrary(path);
}

// Risultati ////////////////////////////////////////////////////////////////////////////////////////
void InfoView::onResultAddArticle(QWeakPointer<Model::AbstractArticle> new_article) {
    shown_article = new_article;
    buildPage(new_article);
    showArticleInfoDirectly();
}

void InfoView::onResultCancelEdit() {
    showArticleInfoDirectly();
    buildEditor(shown_article);
}

void InfoView::onResultCancelNewArticle() {
    buildPage(shown_article);
    showArticleInfoDirectly();
}

void InfoView::onResultEditArticle(QWeakPointer<Model::AbstractArticle> article) {
    buildPage(article);
    showArticleInfoDirectly();
}

void InfoView::onResultFavoriteArticle(QWeakPointer<AbstractArticle> article) {
    if (article == shown_article) {
        emit resultFavoriteArticle(article);
    }
}

void InfoView::onResultLoadLibrary(Library&) {
    _info_container->clearWidget();
    _edit_container->clearWidget();
}
