#ifndef FAVORITEBUTTON_H
#define FAVORITEBUTTON_H

#include <QPushButton>

class FavoriteButton : public QPushButton
{
    Q_OBJECT

private:
    bool state;

public:
    explicit FavoriteButton(bool initial_state = false, QWidget *parent = nullptr);


public slots:
    void update();
    void changeState(bool new_state);

signals:
};

#endif // FAVORITEBUTTON_H
