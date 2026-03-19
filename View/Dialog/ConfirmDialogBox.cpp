#include "ConfirmDialogBox.h"

#include <QLayout>
#include <QLocale>
#include <QString>

#include "Utils/Global.h"
#include "Utils/Style.h"

using namespace Utils::Global;


ConfirmDialogBox::ConfirmDialogBox(const QString& text, const QMessageBox::Icon& icon, QWidget *parent)
    : QMessageBox{parent}
{
    layout()->setAlignment(Qt::AlignCenter);
    setIcon(icon);
    setLocale(QLocale::Italian);
    setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    setStyleSheet(Utils::Style::load(":/assets/style/ConfirmDialogBox.qss"));
    setText(text);
    setWindowTitle(APP_NAME);
}

bool ConfirmDialogBox::ask() {
    int ret = exec();

    switch (ret) {
    case QMessageBox::Yes:
        return true;

    case QMessageBox::No:
        return false;

    default:
        return false;
    }
}
