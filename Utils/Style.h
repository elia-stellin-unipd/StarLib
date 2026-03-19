#ifndef UTILS_STYLE_H
#define UTILS_STYLE_H

#include <QString>
#include <QIcon>

namespace Utils::Style {
    QString load(const QString& stylesheet_path);

    namespace Icons {

        QPixmap getColored(const QPixmap& source, QColor color);

    const QString
        FAVORITE_ON     (":/assets/icons/star-on.png"),
        FAVORITE_OFF    (":/assets/icons/star-off.png"),
        FAVORITE_WHITE  (":/assets/icons/star-white.png"),
        TRASH           (":/assets/icons/trash-solid.png"),
        PLUS_SOLID      (":/assets/icons/plus-solid.png"),
        PLUS_LIGHT      (":/assets/icons/plus-light.png"),
        EDIT_GRAY       (":/assets/icons/edit-gray.png"),
        EDIT_WHITE      (":/assets/icons/edit-white.png"),
        BOOK            (":/assets/icons/book-solid.png"),
        FILM            (":/assets/icons/film-solid.png"),
        NEWSPAPER       (":/assets/icons/newspaper-solid.png"),
        FILE            (":/assets/icons/file-solid.png"),
        FILE_NEW        (":/assets/icons/file-circle-plus-solid.png"),
        FILE_EDIT       (":/assets/icons/file-pen-solid.png"),
        FILE_EDIT_GRAY  (":/assets/icons/file-pen-solid-gray.png"),
        FLOPPY_DISK     (":/assets/icons/floppy-disk-solid.png"),
        FLOPPY_DISK_GRAY(":/assets/icons/floppy-disk-solid-gray.png")
        ;
    }
}

#endif // UTILS_STYLE_H
