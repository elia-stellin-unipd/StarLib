#include "InfoPageContainer.h"


InfoPageContainer::InfoPageContainer(QWidget *parent)
    : PageContainer{parent}
{}

QPointer<InfoBase> InfoPageContainer::getWidget() const {
    InfoBase *info_base = qobject_cast<InfoBase*>(PageContainer::getWidget().get());
    return QPointer<InfoBase>(info_base);
}

void InfoPageContainer::setWidget(InfoBase *new_widget) {
    PageContainer::setWidget(new_widget);
}
