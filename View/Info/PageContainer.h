#ifndef PAGECONTAINER_H
#define PAGECONTAINER_H

#include <QPointer>
#include <QWidget>

#include "Visitors/ArticleInfoWidget.h"

class PageContainer : public QWidget
{
    Q_OBJECT

private:
   QPointer<QWidget> _info_widget;

public:
    explicit PageContainer(QWidget *parent = nullptr);

    QPointer<QWidget> getWidget() const;
    void setWidget(QWidget *new_widget);

    void clearWidget();

signals:
};

#endif // PAGECONTAINER_H
