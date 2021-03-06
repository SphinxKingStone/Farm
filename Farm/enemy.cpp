#include "enemy.h"
#include <QDebug>

Enemy::Enemy(Beast beast)
{
    beast_id = beast.id;
    max_health = beast.health;
    health = max_health;
    defense = beast.defense;
    agility = beast.agility;
    concentration = beast.concentration;
    attack = beast.attack;
    xp_reward = beast.xp;
    lvl = beast.lvl;
    image = beast.image;
    name = beast.name;
    forward_timer = new QTimer();
    QObject::connect(forward_timer, SIGNAL(timeout()), this, SLOT(forward_timer_tick()));
    backward_timer = new QTimer();
    QObject::connect(backward_timer, SIGNAL(timeout()), this, SLOT(backward_timer_tick()));
    // выделение и удаление памяти можно делать после движения, но я сделал так, потому что
    // экземпляры и так существуют недолго, плюс, так легче читается код

    // Мои личные предпочтения по скорости анимации
    animation_speed = new int(2);
    pixel_step = new qreal(0.46);
}

Enemy::~Enemy()
{
    delete forward_timer;
    delete backward_timer;
    delete item;
    delete animation_speed;
    delete pixel_step;
}

int Enemy::get_beast_id()
{
    return beast_id;
}

QPixmap Enemy::get_image()
{
    return image;
}

int Enemy::get_max_health()
{
    return max_health;
}

int Enemy::get_health()
{
    if (health < 0)
        return 0;
    else
        return health;
}

int Enemy::get_attack()
{
    return attack;
}

int Enemy::get_xp()
{
    return xp_reward;
}

QString Enemy::get_name()
{
    return name;
}

int Enemy::hit()
{
    //заменить 40 на константу - скорость передвижения
    forward_timer->setInterval(*animation_speed);
    x_coord = new qreal();
    *x_coord = item->x();
    forward_timer->start();


    backward_timer->setInterval(*animation_speed);

    //учесть что надо при атаке, шанс промаха, крита и т.д.
    int tmp_attack = attack;
    int atk_discrepancy;

    atk_discrepancy = (qrand () % 38) - 19;
    tmp_attack += round(double(attack * (atk_discrepancy)) / 100);

    double crit_chance; // случайное от 0.0625 до 100
    double my_crit_chance; // шанс блока от 0 до 100 с шагом в 0.0625
    crit_chance = (double)qrand() / RAND_MAX;
    crit_chance = (0.0625 + (crit_chance) * (100.0 - 0.0625));
    my_crit_chance = concentration * 0.0625;

    if (my_crit_chance >= crit_chance)
        tmp_attack *= 1.75;

    return tmp_attack;
}

int Enemy::get_hit(int amount, QString type)
{
    //кейсим тип, если магический, то одна защита, если физический, то другой

    // блок
    if (avoid(defense, 0.004))
        return -1;

    // уворот
    if (avoid(agility, 0.0625))
        return 0;

    double armor_absorption;

    armor_absorption = amount * (defense * 0.0125);
    armor_absorption /= 100;
    amount -= round(armor_absorption);

    // чтобы при очень сильной защите здоровье в плюс не уходило
    if (amount < 0)
        amount = 0;

    health -= amount;
    return amount;
}

void Enemy::set_item(QGraphicsPixmapItem *new_item, QGraphicsPixmapItem *players_item)
{
    item = new_item;
    item->setPos(700 - item->boundingRect().width(), players_item->y() + players_item->boundingRect().height() - item->boundingRect().height());
}

QGraphicsPixmapItem *Enemy::get_item()
{
    return item;
}

void Enemy::forward_timer_tick()
{    
    item->setPos(item->x() - *pixel_step, item->y());

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

void Enemy::backward_timer_tick()
{
    item->setPos(item->x() + *pixel_step, item->y());
    if (item->x() >= *x_coord)
    {
        delete x_coord;
        backward_timer->stop();

        if (health > 0)
        {
            emit is_alive();
        }
    }
}
