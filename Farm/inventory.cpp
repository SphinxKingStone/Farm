#include "inventory.h"
#include <QDebug>

Inventory::Inventory(Player *p)
{
    player = p;

    menu = new QMenu;
    menu->setStyleSheet("color: white;"
                        "background-color: rgba(255,255,255,100);");

    signalMapperE = new QSignalMapper();
    QObject::connect(signalMapperE, SIGNAL(mapped(int)), this, SLOT(equip(int)));

    signalMapperS = new QSignalMapper();
    QObject::connect(signalMapperS, SIGNAL(mapped(int)), this, SLOT(sell(int)));

    signalMapperT = new QSignalMapper();
    QObject::connect(signalMapperT, SIGNAL(mapped(int)), this, SLOT(throw_out(int)));
}

bool Inventory::equip(int id)
{
    //сперва удаляем предмет из инвентаря
    Item * tmp_item = new Item();
    *tmp_item = player->get_item(id);
    player->remove_item(id);
    emit item_deleted();
    // теперь надо надевать предмет на соответствующую ячейку (else if)
    if (tmp_item->type == "weapon")
    {
        player->equip_item("weapon", *tmp_item);
        emit item_equiped("weapon", tmp_item->image);
    }
    else if (tmp_item->type == "helmet")
    {
        player->equip_item("head", *tmp_item);
        emit item_equiped("head", tmp_item->image);
    }
    delete tmp_item;
}

void Inventory::sell(int id)
{
    player->increase_money(player->get_items()[id].cost);
    player->remove_item(id);
    emit item_deleted();
    qDebug() << "Emit прошел";
}

void Inventory::throw_out(int id)
{
    player->remove_item(id);
    emit item_deleted();
}

void Inventory::onMenu_close()
{
    qDebug() << "SLOOOT";
}

Inventory::onCell_click()
{
    qDebug() << "click";
}

Inventory::onCell_right_click(int id)
{
    //если в выбраной клетке оружие, то его можно надеть
    if ((player->get_item(id).type == "weapon") || (player->get_item(id).type == "helmet"))
    {
        equipA = menu->addAction(QIcon(":/images/equip.png"),"Надеть");
        signalMapperE->setMapping(equipA, id);
        QObject::connect(equipA, SIGNAL(triggered(bool)), signalMapperE, SLOT(map()));
    }

    sellA = menu->addAction(QIcon(":/images/coin.png"), "Продать");
    signalMapperS->setMapping(sellA, id);
    QObject::connect(sellA, SIGNAL(triggered(bool)), signalMapperS, SLOT(map()));

    throw_outA = menu->addAction(QIcon(":/images/trash_can.png"),"Выкинуть");
    signalMapperT->setMapping(throw_outA, id);
    QObject::connect(throw_outA, SIGNAL(triggered(bool)), signalMapperT, SLOT(map()));

    menu->exec(QCursor::pos());
    menu->clear();
}
