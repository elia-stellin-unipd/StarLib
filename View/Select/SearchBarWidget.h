#ifndef SEARCHBARWIDGET_H
#define SEARCHBARWIDGET_H

#include <QCheckBox>
#include <QLineEdit>
#include <QWidget>
#include <QList>

#include "Model/Search/Query.h"

class SearchBarWidget : public QWidget
{
    Q_OBJECT

private:
    QLineEdit* _line_edit;      // la barra di ricerca
    QList<QCheckBox*> _options;  // opzioni della ricerca

public:    
    explicit SearchBarWidget(QWidget *parent = nullptr);

    void emitSearch();

public slots:
    void setFocus();

signals:
    void searchQuery(Model::Search::Query query);
};

#endif // SEARCHBARWIDGET_H
