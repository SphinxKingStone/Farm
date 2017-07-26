#include "player.h"
#include <QDebug>

std::vector<std::pair<int, int>> level_xp;

Player::Player()
{
    //Todo: инициализировать не в конструкторе, а как - то единожды, при запуске программы
    for (int i = 0; i < 100; i++)
    {
        level_xp.insert(level_xp.end(), std::make_pair(i, i * 50));
    }

    max_health = 200;
    health = max_health;
    attack = 45;
    xp = 0;
    lvl = 1;
    defense = 80;
    concentration = 20;
    agility = 20;
    skill_point = 0;
    money = 0;

    //Вызывает libpng warning: iCCP: known incorrect sRGB profile
    image = QPixmap(":/images/main_hero.png").scaled(150, 200, Qt::KeepAspectRatio);
}

Player::~Player()
{
    /*
    delete forward_timer;
    delete backward_timer;
    delete item;
    */
}

void Player::delete_after_battle()
{
    delete forward_timer;
    delete backward_timer;
    delete item;
    delete animation_speed;
    delete pixel_step;
}

void Player::delete_item()
{
    delete item;
}

void Player::increase_xp(int amount)
{
    xp += amount;
    if (xp >= level_xp[lvl].second)
        increase_lvl();

}

void Player::increase_lvl()
{
    lvl++;
    max_health += 20;
    attack += 10;
    skill_point += 2;
    restore_health();
}

void Player::increase_defense(int amount)
{
    defense += amount;
}

void Player::increase_agility(int amount)
{
    agility += amount;
}

void Player::increase_concentration(int amount)
{
    concentration += amount;
}

void Player::increase_money(int amount)
{
    money += amount;
}

void Player::decrease_skill_points()
{
    skill_point--;
}



int Player::get_hit(int amount, QString type)
{
    // кейсим тип, если магический, то одна защита, если физический, то другой

    // блок
    if (avoid(defense, 0.004))
        return -1;

    // уворот
    if (avoid(agility, 0.0625))
        return 0;


    double * armor_absorption = new double();

    *armor_absorption = amount * (defense * 0.0125);
    *armor_absorption /= 100;
    amount -= round(*armor_absorption);

    delete armor_absorption;

    // чтобы при очень сильной защите здоровье в плюс не уходило
    if (amount < 0)
        amount = 0;

    health -= amount;
    return amount;
}

int Player::hit()
{
    // анимация подхода
    forward_timer->setInterval(*animation_speed);
    x_coord = new qreal();
    *x_coord = item->x();
    forward_timer->start();


    backward_timer->setInterval(*animation_speed);

    // здесь учесть все вещи, текущую атаку, шанс крита, шанс промаха и т.д.
    // расхождение урона в 19%; min - 81 %, max - 119% от текущей атаки
    int tmp_attack = attack;
    int * atk_discrepancy = new int();

    *atk_discrepancy = (qrand () % 39) - 19;
    tmp_attack += round(double(attack * (*atk_discrepancy)) / 100);

    delete atk_discrepancy;

    double * crit_chance = new double(); // случайное от 0.0625 до 100
    double * my_crit_chance = new double(); // шанс блока от 0 до 100 с шагом в 0.0625
    *crit_chance = (double)qrand() / RAND_MAX;
    *crit_chance = (0.0625 + (*crit_chance) * (100.0 - 0.0625));
    *my_crit_chance = concentration * 0.0625;

    if (*my_crit_chance >= *crit_chance)
        tmp_attack *= 1.75;

    delete my_crit_chance;
    delete crit_chance;

    return tmp_attack;
}

void Player::restore_health()
{
    health = max_health;
}

int Player::get_level()
{
    return lvl;
}

int Player::get_xp()
{
    return xp;
}

int Player::get_max_health()
{
    return max_health;
}

int Player::get_health()
{
    if (health < 0)
        return 0;
    else
        return health;
}

int Player::get_attack()
{
    return attack;
}

int Player::get_defense()
{
    return defense;
}

int Player::get_agility()
{
    return agility;
}

int Player::get_concentration()
{
    return concentration;
}

int Player::get_xp_for_next_lvl()
{
    return level_xp[lvl].second;
}

int Player::get_skill_point()
{
    return skill_point;
}

int Player::get_money()
{
    return money;
}

void Player::set_item(QGraphicsPixmapItem * new_item, qreal x, qreal y)
{
    item = new_item;
    item->setPos(x, y);
}

QGraphicsPixmapItem *Player::get_item()
{
    return item;
}

QPixmap Player::get_image()
{
    return image;
}

void Player::allocate_timers()
{
    forward_timer = new QTimer();
    QObject::connect(forward_timer, SIGNAL(timeout()), this, SLOT(forward_timer_tick()));
    backward_timer = new QTimer();
    QObject::connect(backward_timer, SIGNAL(timeout()), this, SLOT(backward_timer_tick()));

    // Мои личные предпочтения по скорости анимации
    animation_speed = new int(1);
    pixel_step = new qreal(0.23);
}

bool Player::add_item(Item item)
{
    if (items.size() >= 56)
        return false;
    else
    {
        items.insert(items.end(), item);
        return true;
    }
    return false;
}

std::vector<Item> Player::get_items()
{
    return items;
}

void Player::remove_item(std::vector<Item>::iterator it)
{
    qDebug() << (*it).name;
    items.erase(it);
}

void Player::forward_timer_tick()
{
    item->setPos(item->x() + *pixel_step, item->y());

    QList<QGraphicsItem *> colliding_items = item->collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(QGraphicsPixmapItem))
        {
            forward_timer->stop();
            backward_timer->start();
            emit hit_is_done();
        }
    }

    colliding_items.clear();
}

void Player::backward_timer_tick()
{
    item->setPos(item->x() - *pixel_step, item->y());
    if (item->x() <= *x_coord)
    {
        backward_timer->stop();
        delete x_coord;

        if (health > 0)
        {
            emit is_alive();
        }
    }
}
