#ifndef ARTICLEEDITINFOWIDGET_H
#define ARTICLEEDITINFOWIDGET_H

#include <QFormLayout>
#include <QWidget>

#include "Model/AbstractPublication.h"

#include "View/Info/Editor/EditInfoBase.h"

#include "Visitors/ArticleConstVisitor.h"

namespace Visitors {
class ArticleEditInfoWidget : public ArticleConstVisitor
{

private:

    EditInfoBase *widget;
    /// @brief è true se è il widget corrispondente è stato modificato
    bool was_edited;

    void connectBase();
    void connectPublication();
    void connectBook();
    void connectIssue();
    void connectMovie();

public:
    EditInfoBase *getWidget() const;
    ArticleEditInfoWidget(): was_edited(false) {}

    void visit(const Model::Book& book) override;
    void visit(const Model::Movie& movie) override;
    void visit(const Model::MagazineIssue& magazine) override;
};
}

#endif // ARTICLEEDITINFOWIDGET_H
