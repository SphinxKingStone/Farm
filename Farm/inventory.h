#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMap>
#include "clickablelabel.h"
#include <QMenu>


class Inventory: public QObject
{
    Q_OBJECT
public:
    Inventory();

    QMap<int, ClickableLabel*> cells;
public slots:
    onCell_click();
    onCell_right_click(int id);
};

#endif // INVENTORY_H
