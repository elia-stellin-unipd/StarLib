#ifndef CONFIRMDIALOGBOX_H
#define CONFIRMDIALOGBOX_H

#include <QMessageBox>

class ConfirmDialogBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit ConfirmDialogBox(
        const QString& text, const QMessageBox::Icon& icon = QMessageBox::Question,
        QWidget *parent = nullptr
    );

    /// @brief Chiedi conferma all'utente. Ritorna true se la conferma è stata data, false altrimenti.
    bool ask();

signals:
};

#endif // CONFIRMDIALOGBOX_H
