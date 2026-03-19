#ifndef EDITINFOBASE_H
#define EDITINFOBASE_H

#include <QFormLayout>
#include <QPointer>
#include <QWidget>

#include "Model/AbstractArticle.h"

class EditInfoBase : public QWidget
{
    Q_OBJECT

private:
    QFormLayout *_form_layout;
    bool _was_edited;

public:
    explicit EditInfoBase(const Model::AbstractArticle& article, QWidget *parent = nullptr);

    QFormLayout * mainLayout() const;
    bool wasEdited() const;

signals:
    // Richieste
    /// @brief Richiede di applicare le modifiche all'articolo corrente
    void requestEditCurrent(QPointer<EditInfoBase>); // -> InfoView

    // Risultati
    void resultCancelEdit(); //


public slots:

    /// @brief Chiamato ogni volta che si modifica il form
    void onEdit();

    // Richieste
    void onRequestCancelEdit(); // <- InfoView
};

#endif // EDITINFOBASE_H
