#include "PageContainer.h"

#include <QPointer>
#include <QVBoxLayout>

using namespace Visitors;

PageContainer::PageContainer(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignTop);
}

QPointer<QWidget> PageContainer::getWidget() const {
    return QPointer<QWidget>(_info_widget.get());
}

void PageContainer::clearWidget() {
    if (_info_widget.get()) {
        layout()->removeWidget(_info_widget.get());
        _info_widget.get()->deleteLater();
    }
}

void PageContainer::setWidget(QWidget *new_widget) {
    // Elimina vecchio oggetto e mostra nuovo
    clearWidget();
    layout()->addWidget(new_widget);
    _info_widget = new_widget;
}
