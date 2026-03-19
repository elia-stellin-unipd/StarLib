#ifndef INFOPAGECONTAINER_H
#define INFOPAGECONTAINER_H

#include <QWidget>

#include "View/Info/PageContainer.h"
#include "View/Info/InfoBase.h"

class InfoPageContainer : public PageContainer
{
    Q_OBJECT
public:
    explicit InfoPageContainer(QWidget *parent = nullptr);

    QPointer<InfoBase> getWidget() const;
    void setWidget(InfoBase *new_widget);

signals:
};

#endif // INFOPAGECONTAINER_H
