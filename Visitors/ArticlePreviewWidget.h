#ifndef ARTICLEPREVIEWWIDGET_H
#define ARTICLEPREVIEWWIDGET_H

#include <QWeakPointer>
#include <QWidget>

#include "Model/Book.h"
#include "Model/Movie.h"
#include "Model/MagazineIssue.h"

#include "View/Select/ArticlePreviewBase.h"

#include "ArticleVisitor.h"

class QWidget;

namespace Visitors {

    class ArticlePreviewWidget: public ArticleConstVisitor {

    private:
        ArticlePreviewBase *widget;

        void populateWidget(const QString& title, const QIcon& icon, const QString& secondary_text);

    public:
        ArticlePreviewBase *getWidget();

        /// @brief prende in input l'articolo usato per costruire ArticlePreviewBase
        ArticlePreviewWidget(QWeakPointer<Model::AbstractArticle> article);
        void visit(const Model::Book &book) override;
        void visit(const Model::Movie &movie) override;
        void visit(const Model::MagazineIssue &magazine) override;

    };
};

#endif // ARTICLEPREVIEWWIDGET_H
