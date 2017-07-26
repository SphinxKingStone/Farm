#include "inventory.h"
#include <QDebug>

Inventory::Inventory(Player *p)
{
    player = p;
}

bool Inventory::equip(int id)
{/*
    if (player->get_items()[id].type == "weapon")
    {
        profile_cells["weapon"]->setPixmap(player->get_items()[id].image);
        return true;
    }
    return false;*/
}

void Inventory::sell(int id)
{
    player->increase_money(player->get_items()[id].cost);
    //удаляем предмет из инвентаря по id
    std::vector<Item>::iterator it = (player->get_items().begin() + id);
    qDebug() << id;
    player->remove_item(it);
    emit item_deleted();
    qDebug() << "Emit прошел";
}

Inventory::onCell_click()
{
    qDebug() << "click";
}

Inventory::onCell_right_click(int id)
{
    qDebug() << "right click";
    //Надо чистить память
    QMenu * menu = new QMenu;
    signalMapper = new QSignalMapper();
    //если в выбраной клетке оружие, то его можно надеть
//    добавить броню и т.д.
    if (player->get_items()[id].type == "weapon")
    {

    QAction * equip = menu->addAction(QIcon(":/images/equip.png"),"Надеть");
    signalMapper->setMapping(equip, id);
    QObject::connect(equip, SIGNAL(triggered(bool)), signalMapper, SLOT(map()));
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(equip(int)));
    }


    QAction * sell = menu->addAction(QIcon(":/images/coin.png"), "Продать");
    signalMapper->setMapping(sell, id);
    QObject::connect(sell, SIGNAL(triggered(bool)), signalMapper, SLOT(map()));
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(sell(int)));

    QAction * throw_out = menu->addAction(QIcon(":/images/trash_can.png"),"Выкинуть");
    connect(throw_out, SIGNAL(triggered(bool)), this, SLOT(onCell_click()));

    menu->setStyleSheet("color: white;"
                        "background-color: rgba(255,255,255,100);");
    menu->exec(inventory_cells[0]->mapToGlobal(inventory_cells[id]->pos()));
}
