#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMap>
#include "clickablelabel.h"
#include <QMenu>
#include "beast_n_drop.h"
#include "player.h"
#include "inventory.h"


class Inventory: public QObject
{
    Q_OBJECT
public:
    Inventory(Player *p);

    QMap<int, QLabel*> inventory_cells;
    QMap<QString, ClickableLabel*> profile_cells;

private:
    Player * player;

private slots:
    bool equip(int id);
    void sell(int id);

public slots:
    onCell_click();
    onCell_right_click(int id);

signals:
    void item_deleted();
};

#endif // INVENTORY_H
