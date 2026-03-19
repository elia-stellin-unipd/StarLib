#include "ArticlePreviewWidget.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QRgb>

#include "View/Select/ArticlePreviewBase.h"

#include "Utils/Style.h"


namespace Visitors {
    using namespace Model;

    ArticlePreviewBase* ArticlePreviewWidget::getWidget() {
        return widget;
    }

    ArticlePreviewWidget::ArticlePreviewWidget(QWeakPointer<Model::AbstractArticle> article):
        widget(new ArticlePreviewBase(article))
    {}

    void ArticlePreviewWidget::populateWidget(
        const QString& title, const QIcon& icon, const QString& secondary_text
    ) {
        using namespace Utils::Style;
        QLabel *title_label = new QLabel(QString("<b>%1</b>").arg(title));
        widget->mainLayout()->addWidget(title_label, 0, 0);

        QLabel *icon_label = new QLabel();

        icon_label->setPixmap(
            Icons::getColored(icon.pixmap(80), QColor(255, 255, 255, 100))
        );
        widget->mainLayout()->addWidget(icon_label, 1, 0, 1, 2);

        QLabel *authors_label = new QLabel(secondary_text);
        authors_label->setStyleSheet("QLabel { color: #bbb; }");
        widget->mainLayout()->addWidget(authors_label, 2, 0, 1, 2);
    }

    void ArticlePreviewWidget::visit(const Book &book) {
        populateWidget(
            book.getTitle(),
            QIcon(Utils::Style::Icons::BOOK),
            book.getAuthors().join(", ")
        );
    }

    void ArticlePreviewWidget::visit(const Movie &movie) {
        populateWidget(
            movie.getTitle(),
            QIcon(Utils::Style::Icons::FILM),
            QString::fromStdString(movie.getLength().getString())
        );
    }

    void ArticlePreviewWidget::visit(const MagazineIssue &issue) {
        populateWidget(
            issue.getTitle(),
            QIcon(Utils::Style::Icons::NEWSPAPER),
            "Uscita #" + QString::number(issue.getIssueNumber())
        );
    }
};
