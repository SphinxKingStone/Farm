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
    QObject::connect(signalMapperT, SIGNAL(mapped(QString)), this, SLOT(unequip(QString)));

//    equippable_types["тип"] = "место";

    equippable_types["weapon"] = "hands";
    equippable_types["shoulder_armor"] = "shoulders";
    equippable_types["helmet"] = "head";
    equippable_types["boots"] = "feet";
    equippable_types["arms_armor"] = "arms";
    equippable_types["breastplate"] = "body";
    equippable_types["legs_armor"] = "legs";
}

void Inventory::equip(int id)
{
    Item tmp_item = player->get_item(id);

//    ищем тип выбранного предмета в контейнере предметов, которые можно надевать
    auto it = equippable_types.find(tmp_item.type);

    player->equip_item((*it).second, tmp_item);

//    удаляем предмет из инвентаря
    player->remove_item(id);
    emit item_deleted();
}

void Inventory::sell(int id)
{
    player->increase_money(player->get_items()[id].cost);
    player->remove_item(id);
    emit item_deleted();
}

void Inventory::throw_out(int id)
{
    player->remove_item(id);
    emit item_deleted();
}

void Inventory::unequip(QString place)
{
    player->unequip_item(place);
    emit item_deleted();
}

void Inventory::onCell_click()
{
    qDebug() << "click";
}

void Inventory::onCell_right_click(int id)
{
    auto it = equippable_types.find(player->get_item(id).type); // ищем тип выбранного предмета в контейнере предметов, которые можно надевать
    if (it != equippable_types.end())
        if (player->get_equipped_items()[(*it).second].name == "") //если вещь этого типа не надета на персонаже, тогда её можно надеть
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

void Inventory::onPlayers_cell_right_click(QString place)
{
//    libpng warning: iCCP: known incorrect sRGB profile
    unequipA = menu->addAction(QIcon(":/images/white_man.png"), "Снять");
    signalMapperT->setMapping(unequipA, place);
    QObject::connect(unequipA, SIGNAL(triggered(bool)), signalMapperT, SLOT(map()));

    menu->exec(QCursor::pos());
    menu->clear();
}
