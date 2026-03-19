#ifndef ERRORDIALOGBOX_H
#define ERRORDIALOGBOX_H

#include <QMessageBox>
#include <QWidget>
#include "Model/DataMapper/JsonFile.h"

class ErrorDialogBox : public QMessageBox
{
    Q_OBJECT

public:
    explicit ErrorDialogBox(const QString& text, QMessageBox::Icon icon = QMessageBox::Warning, QWidget *parent = nullptr);
    explicit ErrorDialogBox(Model::DataMapper::JsonFile::FileError error, QWidget *parent = nullptr);

signals:
};

#endif // ERRORDIALOGBOX_H
