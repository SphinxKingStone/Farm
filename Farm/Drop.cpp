#include "drop.h"
#include <QListWidget>
#include <vector>
#include <QDebug>
#include <time.h>



Drop::Drop()
{
    fill_beast_mas(beast_mas);
    fill_drop_mas(drop_mas);
}


int Drop::simulate_drop(int beast_type)
{
    tmp_drop.clear();

    int * BeastType = new int(beast_type);
    int * DropChance = new int(rand() % 100);

    // Число 9999 значит, что ничего не выпало, не использутся ноль, потому что для его использования пришлось бы добавить фиктивную, нулевую запись
    // в массив с предметами, как обойти это по красивому у меня идей нет.
    if (*DropChance > beast_mas[*BeastType].drop_chance)
        return 9999;

    if (*DropChance <= beast_mas[*BeastType].drop_chance)
    {
        for (unsigned int i = 0; i < drop_mas.size(); i++)
        {
            if (drop_mas[i].rarity >= beast_mas[*BeastType].rarity)
                tmp_drop.insert(tmp_drop.end(), drop_mas[i]);
        }

        int * DropType = new int(rand() % tmp_drop.size());
        int result = tmp_drop[*DropType].id;

        delete BeastType;
        delete DropChance;
        delete DropType;

        return result;
    }

    return 9999;
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

void Drop::fill_drop_mas(std::vector<Item> &mas)
{
    mas.insert(mas.end(), Item());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Топор";
    mas.back().rarity = 100;
    mas.back().type = "weapon";
    mas.back().image = (QPixmap(":/images/axe.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 100;

    mas.insert(mas.end(), Item());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Железо";
    mas.back().rarity = 75;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/iron.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 300;

    mas.insert(mas.end(), Item());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Бриллиант";
    mas.back().rarity = 15;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/diamond.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 700;

    mas.insert(mas.end(), Item());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Мусор";
    mas.back().rarity = 100;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/garbage.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 10;
}

void Drop::fill_beast_mas(std::vector<Beast> &mas)
{
    // приблизительно 4000 характеристик - максимум, сколько можно набрать с прокачкой и шмотом
    // 8000 def поглащает 100% урона; 8 - 0.1%; 1 - 0.0125%; 80 - 1%;
    // 26700 def дают шанс блока 100%; 4000 - 15%; 1 - 0.004%; 267 - 1%;
    // ловкость и концентрация могут быть около 800, с шмотом и прокачкой, Разница с шансами от def в 5 раз
    // 800 концентрации/ловкости дает 50% шанс крита/уворота; 1600 - 100%; 1 - 0.0625%; 16 - 1%;
    // пусть крит увеличивает урон на 1.75
    mas.insert(mas.end(), Beast());
    mas[mas.size() - 1].id = mas.size() - 1;
    mas[mas.size() - 1].name = "Кабан";
    mas[mas.size() - 1].drop_chance = 100;
    mas[mas.size() - 1].rarity = 100;
    mas[mas.size() - 1].health = 10;
    mas[mas.size() - 1].defense = 500;
    mas[mas.size() - 1].agility = 8;
    mas[mas.size() - 1].concentration = 16;
    mas[mas.size() - 1].xp = 150;
    mas[mas.size() - 1].attack = 50;
    mas[mas.size() - 1].lvl = 1;
    mas[mas.size() - 1].image = (QPixmap(":/images/boar.png").scaled(200, 200, Qt::KeepAspectRatio));
    mas.insert(mas.end(), Beast());
    mas[mas.size() - 1].id = mas.size() - 1;
    mas[mas.size() - 1].name = "Гоблин";
    mas[mas.size() - 1].drop_chance = 75;
    mas[mas.size() - 1].rarity = 75;
    mas[mas.size() - 1].health = 250;
    mas[mas.size() - 1].defense = 1200;
    mas[mas.size() - 1].agility = 30;
    mas[mas.size() - 1].concentration = 50;
    mas[mas.size() - 1].xp = 25;
    mas[mas.size() - 1].attack = 100;
    mas[mas.size() - 1].lvl = 2;
    mas[mas.size() - 1].image = (QPixmap(":/images/goblin.png").transformed(QTransform().scale(-1, 1)).scaled(150, 200, Qt::KeepAspectRatio));
    mas.insert(mas.end(), Beast());
    mas[mas.size() - 1].id = mas.size() - 1;
    mas[mas.size() - 1].name = "Сова";
    mas[mas.size() - 1].drop_chance = 15;
    mas[mas.size() - 1].rarity = 15;
    mas[mas.size() - 1].health = 500;
    mas[mas.size() - 1].defense = 200;
    mas[mas.size() - 1].agility = 100;
    mas[mas.size() - 1].concentration = 16;
    mas[mas.size() - 1].xp = 40;
    mas[mas.size() - 1].attack = 150;
    mas[mas.size() - 1].lvl = 3;
    mas[mas.size() - 1].image = (QPixmap(":/images/owl.png").scaled(250, 200, Qt::KeepAspectRatio));
}
