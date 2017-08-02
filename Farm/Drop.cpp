#include "drop.h"
#include <QListWidget>
#include <vector>
#include <QDebug>
#include <time.h>



Drop::Drop()
{
    fill_beast_mas(beast_mas);
    fill_drop_mas(drop_mas);
    fill_location_mas(location_mas);
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
    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //0
    mas.back().name = "Топор";
    mas.back().rarity = 100;
    mas.back().type = "weapon";
    mas.back().image = (QPixmap(":/images/axe.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 100;
    mas.back().stats["attack"] = 10;
    mas.back().stats["concentration"] = 35;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //1
    mas.back().name = "Железо";
    mas.back().rarity = 75;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/iron.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 300;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //2
    mas.back().name = "Бриллиант";
    mas.back().rarity = 15;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/diamond.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 700;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //3
    mas.back().name = "Мусор";
    mas.back().rarity = 100;
    mas.back().type = "scrap";
    mas.back().image = (QPixmap(":/images/garbage.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 10;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //4
    mas.back().name = "Кожаный шлем";
    mas.back().rarity = 100;
    mas.back().type = "helmet";
    //Вызывает libpng warning: iCCP: known incorrect sRGB profile
    mas.back().image = (QPixmap(":/images/helmet1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 80;
    mas.back().stats["defense"] = 40;
    mas.back().stats["agility"] = 15;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //5
    mas.back().name = "Наплечники Чумы";
    mas.back().rarity = 35;
    mas.back().type = "shoulder_armor";
    mas.back().image = (QPixmap(":/images/shoulders_1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 450;
    mas.back().stats["defense"] = 60;
    mas.back().stats["concentration"] = 25;


    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //6
    mas.back().name = "Кожаные ботинки";
    mas.back().rarity = 80;
    mas.back().type = "boots";
    mas.back().image = (QPixmap(":/images/boots_1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 80;
    mas.back().stats["defense"] = 30;
    mas.back().stats["agility"] = 15;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //7
    mas.back().name = "Кожаные наручи";
    mas.back().rarity = 80;
    mas.back().type = "arms_armor";
    mas.back().image = (QPixmap(":/images/arms_armor_1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 80;
    mas.back().stats["defense"] = 30;
    mas.back().stats["agility"] = 15;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //8
    mas.back().name = "Кожаный нагрудник";
    mas.back().rarity = 80;
    mas.back().type = "breastplate";
    mas.back().image = (QPixmap(":/images/body_armor_1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 80;
    mas.back().stats["defense"] = 45;
    mas.back().stats["agility"] = 25;

    mas.push_back(Item());
    mas.back().id = mas.size() - 1; //9
    mas.back().name = "Утеплённые поножи";
    mas.back().rarity = 70;
    mas.back().type = "legs_armor";
    mas.back().image = (QPixmap(":/images/legs_armor_1.png").scaled(40, 40, Qt::KeepAspectRatio));
    mas.back().cost = 135;
    mas.back().stats["defense"] = 50;
    mas.back().stats["health"] = 10;
}

void Drop::fill_location_mas(std::vector<Location> &mas)
{
    mas.push_back(Location());
    mas.back().name = "Лес";
    mas.back().habitat_beasts.push_back(0);
    mas.back().habitat_beasts.push_back(2);
    mas.back().habitat_beasts.push_back(4);

    mas.push_back(Location());
    mas.back().name = "Тропинка";
    mas.back().habitat_beasts.push_back(1);
    mas.back().habitat_beasts.push_back(2);

    mas.push_back(Location());
    mas.back().name = "Перекрёсток";
    mas.back().habitat_beasts.push_back(3);
    mas.back().habitat_beasts.push_back(4);
}

void Drop::fill_beast_mas(std::vector<Beast> &mas)
{
    // приблизительно 4000 характеристик - максимум, сколько можно набрать с прокачкой и шмотом
    // 8000 def поглащает 100% урона; 8 - 0.1%; 1 - 0.0125%; 80 - 1%;
    // 26700 def дают шанс блока 100%; 4000 - 15%; 1 - 0.004%; 267 - 1%;
    // ловкость и концентрация могут быть около 800, с шмотом и прокачкой, Разница с шансами от def в 5 раз
    // 800 концентрации/ловкости дает 50% шанс крита/уворота; 1600 - 100%; 1 - 0.0625%; 16 - 1%;
    // пусть крит увеличивает урон на 1.75
    mas.push_back(Beast());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Кабан";
    mas.back().drop_chance = 100;
    mas.back().rarity = 100;
    mas.back().health = 100;
    mas.back().defense = 500;
    mas.back().agility = 8;
    mas.back().concentration = 16;
    mas.back().xp = 15;
    mas.back().attack = 50;
    mas.back().lvl = 1;
    mas.back().image = (QPixmap(":/images/boar.png").scaled(200, 200, Qt::KeepAspectRatio));

    mas.push_back(Beast());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Гоблин";
    mas.back().drop_chance = 75;
    mas.back().rarity = 75;
    mas.back().health = 250;
    mas.back().defense = 1200;
    mas.back().agility = 30;
    mas.back().concentration = 50;
    mas.back().xp = 35;
    mas.back().attack = 100;
    mas.back().lvl = 4;
    mas.back().image = (QPixmap(":/images/goblin.png").transformed(QTransform().scale(-1, 1)).scaled(150, 200, Qt::KeepAspectRatio));

    mas.push_back(Beast());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Сова";
    mas.back().drop_chance = 15;
    mas.back().rarity = 15;
    mas.back().health = 500;
    mas.back().defense = 200;
    mas.back().agility = 700;
    mas.back().concentration = 16;
    mas.back().xp = 50;
    mas.back().attack = 150;
    mas.back().lvl = 10;
    mas.back().image = (QPixmap(":/images/owl.png").scaled(250, 200, Qt::KeepAspectRatio));

    mas.push_back(Beast());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Волк";
    mas.back().drop_chance = 65;
    mas.back().rarity = 65;
    mas.back().health = 120;
    mas.back().defense = 700;
    mas.back().agility = 100;
    mas.back().concentration = 100;
    mas.back().xp = 20;
    mas.back().attack = 75;
    mas.back().lvl = 2;
    mas.back().image = (QPixmap(":/images/wolf.png").scaled(180, 180, Qt::KeepAspectRatio));

    mas.push_back(Beast());
    mas.back().id = mas.size() - 1;
    mas.back().name = "Большой_паук";
    mas.back().drop_chance = 85;
    mas.back().rarity = 40;
    mas.back().health = 160;
    mas.back().defense = 500;
    mas.back().agility = 350;
    mas.back().concentration = 100;
    mas.back().xp = 30;
    mas.back().attack = 90;
    mas.back().lvl = 3;
    mas.back().image = (QPixmap(":/images/spider.png").transformed(QTransform().scale(-1, 1)).scaled(220, 270, Qt::KeepAspectRatio));
}
