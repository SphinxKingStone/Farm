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

    signalMapperU = new QSignalMapper();
    QObject::connect(signalMapperU, SIGNAL(mapped(QString)), this, SLOT(unequip(QString)));

//    equippable_types["тип"] = "место";

    equippable_types["weapon"] = "hands";
    equippable_types["shoulder_armor"] = "shoulders";
    equippable_types["helmet"] = "head";
    equippable_types["boots"] = "feet";
    equippable_types["arms_armor"] = "arms";
    equippable_types["breastplate"] = "body";
    equippable_types["legs_armor"] = "legs";

    stats_mas["defense"].first = player->increase_defense;
    stats_mas["health"].first = player->increase_max_health;
    stats_mas["agility"].first = player->increase_agility;
    stats_mas["concentration"].first = player->increase_concentration;
    stats_mas["attack"].first = player->increase_attack;

    stats_mas["defense"].second = player->decrease_defense;
    stats_mas["health"].second = player->decrease_max_health;
    stats_mas["agility"].second = player->decrease_agility;
    stats_mas["concentration"].second = player->decrease_concentration;
    stats_mas["attack"].second = player->decrease_attack;
}

void Inventory::equip(int id)
{
    Item tmp_item = player->get_item(id);

//    из stats_mas получаем указатель на функцию увеличения соответствующей характеристики и передаем значение предмета
    for (auto it = tmp_item.stats.begin(); it != tmp_item.stats.end(); ++it)
        (player->*(stats_mas[it.key()].first))(it.value());

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

void Inventory::unequip(QString place)
{
    Item tmp_item = player->get_equipped_item(place);

    for (auto it = tmp_item.stats.begin(); it != tmp_item.stats.end(); ++it)
        (player->*(stats_mas[it.key()].second))(it.value());

    player->unequip_item(place);
    emit item_deleted();
}

void Inventory::onCell_right_click(int id)
{
    auto it = equippable_types.find(player->get_item(id).type); // ищем тип выбранного предмета в контейнере предметов, которые можно надевать
    if (it != equippable_types.end())
        if (player->get_equipped_items()[(*it).second].name == "") //если вещь этого типа не надета на персонаже, тогда её можно надеть
        {
        equipA = menu->addAction(QIcon(QCoreApplication::applicationFilePath().left(QCoreApplication::applicationFilePath().length() - 8) + "res/equip.png"),"Надеть");
        signalMapperE->setMapping(equipA, id);
        QObject::connect(equipA, SIGNAL(triggered(bool)), signalMapperE, SLOT(map()));
        }

    sellA = menu->addAction(QIcon(QCoreApplication::applicationFilePath().left(QCoreApplication::applicationFilePath().length() - 8) + "res/coin.png"), "Продать");
    signalMapperS->setMapping(sellA, id);
    QObject::connect(sellA, SIGNAL(triggered(bool)), signalMapperS, SLOT(map()));

    menu->exec(QCursor::pos());
    menu->clear();
}

void Inventory::onPlayers_cell_right_click(QString place)
{
//    libpng warning: iCCP: known incorrect sRGB profile
    if (player->get_items().size() < 56)
    {
        unequipA = menu->addAction(QIcon(QCoreApplication::applicationFilePath().left(QCoreApplication::applicationFilePath().length() - 8) + "res/white_man.png"), "Снять");
        signalMapperU->setMapping(unequipA, place);
        QObject::connect(unequipA, SIGNAL(triggered(bool)), signalMapperU, SLOT(map()));

        menu->exec(QCursor::pos());
        menu->clear();
    }
}
