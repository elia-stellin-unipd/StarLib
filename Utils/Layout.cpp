#include "Layout.h"

#include <QWidget>
#include <QLayoutItem>

namespace Utils::Layout {

    // https://stackoverflow.com/questions/4857188/clearing-a-layout-in-qt
    void clear(QLayout *layout) {
        if (!layout) return;

        QLayoutItem *item;
        while((item = layout->takeAt(0))) {
            if (item->layout()) {
                clear(item->layout());
                item->layout()->deleteLater();
            }
            if (item->widget()) {
                item->widget()->deleteLater();
            }
            delete item;
        }
    }
}
