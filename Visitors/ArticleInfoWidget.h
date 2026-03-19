#ifndef ARTICLEINFOWIDGET_H
#define ARTICLEINFOWIDGET_H

#include <QWidget>
#include <QFormLayout>

#include "ArticleConstVisitor.h"

#include "Model/Book.h"
#include "Model/Movie.h"
#include "Model/MagazineIssue.h"

class QWidget;

namespace Visitors {

    class ArticleInfoWidget: public ArticleConstVisitor {
    private:
        QWidget *widget;

        QFormLayout *setBaseWidget(const Model::AbstractArticle& article);
        void setPublicationData(QFormLayout *layout, const Model::AbstractPublication& publication);

    public:
        QWidget *getWidget();
        void visit(const Model::Book &book) override;
        void visit(const Model::Movie &movie) override;
        void visit(const Model::MagazineIssue &magazine) override;
    };

};

#endif
