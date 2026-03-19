#include "NewArticleButton.h"

#include "Utils/Style.h"


NewArticleButton::NewArticleButton(QWidget *parent)
    : QPushButton{parent}
{
    using namespace Utils::Style;
    setStyleSheet(load(":/assets/style/NewArticleButton.qss"));
    setIcon(QIcon(Icons::PLUS_LIGHT));
    setIconSize(sizeHint() * 0.6);
}

