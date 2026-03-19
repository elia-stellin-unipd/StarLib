#ifndef NEWLIBRARYDIALOG_H
#define NEWLIBRARYDIALOG_H

#include <QDialog>
#include <QLineEdit>

class NewLibraryDialog : public QDialog
{
    Q_OBJECT

private:
    bool userChangedFileName;

    QLineEdit *name_line_edit;
    QLineEdit *folder_line_edit;
    QLineEdit *filename_line_edit;

public:
    explicit NewLibraryDialog(QWidget *parent = nullptr);


public slots:
    void nameEdited(const QString& new_name);

};

#endif // NEWLIBRARYDIALOG_H
