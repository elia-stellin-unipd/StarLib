  #include "EditPageContainer.h"

EditPageContainer::EditPageContainer(QWidget *parent)
    : PageContainer{parent}
{}

QPointer<EditInfoBase> EditPageContainer::getWidget() const {
    EditInfoBase *info_base = qobject_cast<EditInfoBase*>(PageContainer::getWidget().get());
    return QPointer<EditInfoBase>(info_base);
}

void EditPageContainer::setWidget(EditInfoBase *new_widget) {
    PageContainer::setWidget(new_widget);
}
