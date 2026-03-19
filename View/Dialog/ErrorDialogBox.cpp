#include "ErrorDialogBox.h"

#include "Utils/Global.h"

ErrorDialogBox::ErrorDialogBox(const QString& text, QMessageBox::Icon icon, QWidget *parent)
    : QMessageBox(icon, "Errore", text, QMessageBox::NoButton, parent) {}

ErrorDialogBox::ErrorDialogBox(Model::DataMapper::JsonFile::FileError error, QWidget *parent)
    : ErrorDialogBox(
        QString("<b>Errore:</b><br> %1").arg(error.what()),
        QMessageBox::Icon::Warning, parent
    ) {}
