#ifndef INVENTORY_H
#define INVENTORY_H

#include <QMap>
#include "clickablelabel.h"
#include <QMenu>
#include <QSignalMapper>
#include "beast_n_drop.h"
#include "player.h"
#include "inventory.h"
#include <QCoreApplication>


class Inventory: public QObject
{
    Q_OBJECT
public:
    Inventory(Player *p);

    QMap<int, QLabel*> inventory_cells;
    QMap<QString, ClickableLabel*> profile_cells;

    std::map<QString, QString> equippable_types;

private:
    Player * player;
    QSignalMapper * signalMapperE;
    QSignalMapper * signalMapperS;
    QSignalMapper * signalMapperU;
    QMenu * menu;
    QAction * equipA;
    QAction * sellA;
    QAction * unequipA;

    typedef void (Player::*inc_func)(int);
    QMap<QString, QPair<inc_func, inc_func>> stats_mas;

private slots:
    void equip(int id);
    void sell(int id);
    void unequip(QString place);

public slots:
    void onCell_right_click(int id);
    void onPlayers_cell_right_click(QString place);

signals:
    void item_deleted();
};

#endif // INVENTORY_H
