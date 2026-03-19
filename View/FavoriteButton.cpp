#include "FavoriteButton.h"

#include "Utils/Style.h"

#include <QDebug>

FavoriteButton::FavoriteButton(bool initial_state, QWidget *parent)
    : QPushButton{parent}, state(initial_state)
{
    update();
    setIconSize(QSize(20, 20));
    setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}

void FavoriteButton::update() {
    using namespace Utils::Style::Icons;
    setIcon(state? QIcon(FAVORITE_ON) : QIcon(FAVORITE_OFF));
}

void FavoriteButton::changeState(bool new_state) {
    state = new_state;
    update();
}
