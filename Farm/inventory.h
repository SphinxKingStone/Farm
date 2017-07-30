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
    QAction * unequipA;

    std::map<QString, QString> equippable_types;

private slots:
    void equip(int id);
    void sell(int id);
    void throw_out(int id);
    void unequip(QString place);

public slots:
    void onCell_click();
    void onCell_right_click(int id);
    void onPlayers_cell_right_click(QString place);

signals:
    void item_deleted();
};

#endif // INVENTORY_H
