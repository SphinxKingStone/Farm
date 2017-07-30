#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMap>
#include "clickablelabel.h"
#include <QMenu>
#include <QSignalMapper>
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
    QSignalMapper * signalMapperT;
    QSignalMapper * signalMapperE;
    QSignalMapper * signalMapperS;
    QMenu * menu;
    QAction * throw_outA;
    QAction * equipA;
    QAction * sellA;

private slots:
    bool equip(int id);
    void sell(int id);
    void throw_out(int id);
    void onMenu_close();

public slots:
    onCell_click();
    onCell_right_click(int id);

signals:
    void item_deleted();
    void item_equiped(QString place, QPixmap image);
};

#endif // INVENTORY_H
