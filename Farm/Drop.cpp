#include "drop.h"
#include <QListWidget>
#include <vector>
#include <QDebug>
#include <time.h>

Drop::Drop()
{

}


void Drop::simulate_drop()
{
    tmp_drop.clear();

    int BeastType = rand() % beast_mas.size();
    int DropChance = rand() % 100;

    if (DropChance > beast_mas[BeastType].drop_chance)
        //list->addItem("Вы убили " + beast_mas[BeastType].name + " и вам ничего не выпало.");

    if (DropChance <= beast_mas[BeastType].drop_chance)
    {
        for (unsigned int i = 0; i < drop_mas.size(); i++)
        {
            if (drop_mas[i].rarity >= beast_mas[BeastType].rarity)
                tmp_drop.insert(tmp_drop.end(), drop_mas[i]);
        }

        int DropType;
        DropType = rand() % tmp_drop.size();
        //list->addItem("Вы убили " + beast_mas[BeastType].name + " и вам выпал " + tmp_drop[DropType].name);
    }
}

Drop::~Drop()
{
    drop_mas.clear();
    drop_mas.shrink_to_fit();
    beast_mas.clear();
    beast_mas.shrink_to_fit();
    tmp_drop.clear();
    tmp_drop.shrink_to_fit();
}

void Drop::fill_drop_mas(std::vector<drop> &mas)
{
    mas.insert(mas.end(), drop());
    mas[0].id = mas.size() - 1;
    mas[0].name = "Леденец";
    mas[0].rarity = 100;
    mas.insert(mas.end(), drop());
    mas[1].id = mas.size() - 1;
    mas[1].name = "Золото";
    mas[1].rarity = 75;
    mas.insert(mas.end(), drop());
    mas[2].id = mas.size() - 1;
    mas[2].name = "Бриллиант";
    mas[2].rarity = 15;
    mas.insert(mas.end(), drop());
    mas[3].id = mas.size() - 1;
    mas[3].name = "Мусор";
    mas[3].rarity = 100;
}

void Drop::fill_beast_mas(std::vector<beast> &mas)
{
    mas.insert(mas.end(), beast());
    mas[0].id = mas.size() - 1;
    mas[0].name = "Кабан";
    mas[0].drop_chance = 100;
    mas[0].rarity = 100;
    mas[0].health = 10;
    mas[0].xp = 5;
    mas.insert(mas.end(), beast());
    mas[1].id = mas.size() - 1;
    mas[1].name = "Гоблин";
    mas[1].drop_chance = 75;
    mas[1].rarity = 75;
    mas[1].health = 30;
    mas[1].xp = 10;
    mas.insert(mas.end(), beast());
    mas[2].id = mas.size() - 1;
    mas[2].name = "Сова";
    mas[2].drop_chance = 15;
    mas[2].rarity = 15;
    mas[2].health = 50;
    mas[2].xp = 20;
}
