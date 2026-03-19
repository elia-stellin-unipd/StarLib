#include "EditInfoBase.h"

#include <QCheckBox>
#include <QDateEdit>
#include <QKeySequence>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QShortcut>
#include <QTextEdit>

#include "View/Dialog/ConfirmDialogBox.h"
#include "View/Form/FormGenerator.h"

using namespace Model;

EditInfoBase::EditInfoBase(const AbstractArticle& article, QWidget *parent)
    : QWidget{parent}, _was_edited(false)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setAlignment(Qt::AlignTop | Qt::AlignLeft);

    // Setup del form di base
    QLabel *title = new QLabel(QString("Modifica %1").arg(article.getTitle()));
    title->setWordWrap(true);
    title->setObjectName("info-article-title");
    vbox->addWidget(title);

    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);

    _form_layout = new QFormLayout(this);

    vbox->addLayout(_form_layout);

    QHBoxLayout *button_layout = new QHBoxLayout();
    button_layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vbox->addLayout(button_layout);

    QPushButton *confirm = new QPushButton("Conferma");
    confirm->setObjectName("confirm-button");
    connect(
        confirm, &QPushButton::pressed,
        [=] { emit requestEditCurrent(QPointer<EditInfoBase>(this)); }
    );
    button_layout->addWidget(confirm);

    QPushButton *cancel = new QPushButton("Annulla");
    connect(
        cancel, &QPushButton::pressed,
        this, &EditInfoBase::onRequestCancelEdit
    );
    button_layout->addWidget(cancel);

    new QShortcut(
        QKeySequence(Qt::Key_Escape),
        this,
        [=]{ onRequestCancelEdit(); }
    );
}

QFormLayout *EditInfoBase::mainLayout() const {
    return _form_layout;
}

bool EditInfoBase::wasEdited() const {
    return _was_edited;
}

// Slots
void EditInfoBase::onRequestCancelEdit() {
    if (_was_edited) {
        ConfirmDialogBox confirm_box("Sei sicuro di voler annullare la modifica?");
        bool confirm = confirm_box.ask();

        if (!confirm) { return; }
    }
    emit resultCancelEdit();
}

void EditInfoBase::onEdit() {
    _was_edited = true;
}
