#include "NewLibraryDialog.h"

#include <QDir>
#include <QStandardPaths>
#include <QLineEdit>
#include <QFileDialog>
#include <QFormLayout>
#include <QRegularExpression>
#include <QPushButton>
#include <QHBoxLayout>

#include "View/Dialog/ErrorDialogBox.h"

NewLibraryDialog::NewLibraryDialog(QWidget *parent)
    : QDialog{parent}, userChangedFileName{false}
{
    setStyleSheet("* { background: #282828; } QLineEdit { background: #121212; }");
    QVBoxLayout *layout = new QVBoxLayout();
    QFormLayout *form = new QFormLayout();

    name_line_edit = new QLineEdit();
    name_line_edit->setObjectName("new_library_name");

    QHBoxLayout *folder_line = new QHBoxLayout();
        QPushButton *search_folder_button = new QPushButton();
        search_folder_button->setText("Cerca");

        folder_line->addWidget(search_folder_button);

        folder_line_edit = new QLineEdit();
        folder_line_edit->setObjectName("new_library_folder");
        folder_line->addWidget(folder_line_edit);

    filename_line_edit = new QLineEdit();
    filename_line_edit->setObjectName("new_library_filename");

    connect(
        search_folder_button, &QPushButton::pressed,
        [=] {
            QString directory = QFileDialog::getExistingDirectory(
                this, "Cartella", QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).at(0)
                );
            folder_line_edit->setText(directory);
        }
    );

    connect(
        name_line_edit, &QLineEdit::textEdited,
        this, &NewLibraryDialog::nameEdited
    );

    connect(
        filename_line_edit, &QLineEdit::textEdited,
        [=] {
            userChangedFileName = true;
        }
    );

    form->addRow("Nome Libreria", name_line_edit);
    form->addRow("Cartella", folder_line);
    form->addRow("Nome File", filename_line_edit);

    layout->addLayout(form);

    QPushButton *accept_button = new QPushButton("Crea libreria");
    layout->addWidget(accept_button);

    connect(
        accept_button, &QPushButton::pressed,
        [=] {
            QDir folder_dir(folder_line_edit->text());
            if (name_line_edit->text().isEmpty()) {
                ErrorDialogBox("Inserire un titolo valido!").exec();
            }
            else if (!(folder_dir.isAbsolute() && folder_dir.exists())) {
                ErrorDialogBox("Inserire una cartella esistente!").exec();
            }
            else if (filename_line_edit->text().isEmpty()) {
                ErrorDialogBox("Inserire un filename valido!").exec();
            }
            else {
                accept();
            }
        }
    );

    setLayout(layout);
}

void NewLibraryDialog::nameEdited(const QString& new_name) {
    QString new_string = new_name;
    new_string.replace(" ", "_").replace(QRegularExpression("[^a-zA-Z0-9_-]"), "");

    if (!userChangedFileName) {
        filename_line_edit->setText(
            new_string + ".json"
        );
    }
}
