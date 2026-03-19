#include "ArticleInfoWidget.h"

#include <QLabel>
#include <QPushButton>

#include "View/Info/InfoBase.h"

namespace Visitors {
    using namespace Model;
    QWidget* ArticleInfoWidget::getWidget() {
        return widget;
    }

    void ArticleInfoWidget::setPublicationData(QFormLayout *layout, const Model::AbstractPublication& publication) {
        layout->addRow(
            "Autori", new QLabel(publication.getAuthors().join(", "))
            );

        layout->addRow(
            "Editore", new QLabel(publication.getPublisher())
            );

        layout->addRow(
            "N° di pagine", new QLabel(QString::number(publication.getPageNumber()))
            );
    }

    void ArticleInfoWidget::visit(const Book &book) {
        InfoBase *base = new InfoBase(book);
        widget = base;
        QFormLayout *form = base->mainLayout();
        setPublicationData(form, book);

        form->addRow(
            "ISBN", new QLabel(book.getISBN())
        );
    }

    void ArticleInfoWidget::visit(const MagazineIssue &issue) {
        InfoBase *base = new InfoBase(issue);
        widget = base;
        QFormLayout *form = base->mainLayout();
        setPublicationData(form, issue);

        form->addRow(
            "N° uscita", new QLabel(QString::number(issue.getIssueNumber()))
            );

        form->addRow(
            "ISSN", new QLabel(issue.getISSN())
            );
    }

    void ArticleInfoWidget::visit(const Movie &movie) {
        InfoBase *base = new InfoBase(movie);
        widget = base;
        QFormLayout *form = base->mainLayout();

        form->addRow("Regista", new QLabel(movie.getDirector()));

        form->addRow("Durata", new QLabel(QString::fromStdString(movie.getLength().getString())));
    }

};
