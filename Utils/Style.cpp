#include "Style.h"

#include <QFile>
#include <QPainter>
#include <QPixmap>

#include <QDebug>

namespace Utils::Style {

    namespace Icons {
        QPixmap getColored(const QPixmap& source, QColor color) {
            QPixmap dest = source;
            QPainter painter(&dest);
            painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            painter.fillRect(dest.rect(), color);
            painter.end();
            return dest;
        }
    }

    QString load(const QString& stylesheet_path) {
        QFile stylesheet(stylesheet_path);
        stylesheet.open(QFile::ReadOnly);
        return QString(stylesheet.readAll());
    }
}
