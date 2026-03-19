#include "FormValidator.h"

#include <QLineEdit>
#include <QMessageBox>

#include "Utils/Global.h"

#include "View/Form/FormGenerator.h"

namespace Form {

    bool validate(QFormLayout *form) {
        QLineEdit *edit_title = form->parent()->findChild<QLineEdit*>(TITLE);

        if (edit_title && edit_title->text().isEmpty()) {
            QMessageBox msgBox = QMessageBox(QMessageBox::Icon::Warning, Utils::Global::APP_NAME, "Inserire il titolo dell'articolo.");
            msgBox.exec();
            return false;
        }

        return true;
    }
}
