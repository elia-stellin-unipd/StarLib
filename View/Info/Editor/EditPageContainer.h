#ifndef EDITPAGECONTAINER_H
#define EDITPAGECONTAINER_H

#include <QPointer>
#include <QWidget>

#include "../PageContainer.h"
#include "View/Info/Editor/EditInfoBase.h"

class EditPageContainer : public PageContainer
{
    Q_OBJECT
public:
    explicit EditPageContainer(QWidget *parent = nullptr);

    QPointer<EditInfoBase> getWidget() const;
    void setWidget(EditInfoBase *new_widget);

signals:
};

#endif // EDITPAGECONTAINER_H
