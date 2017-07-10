#include "enemy.h"

Enemy::Enemy(Beast beast)
{
    max_health = beast.health;
    health = max_health;
    attack = beast.attack;
    xp_reward = beast.xp;
    lvl = beast.lvl;
    image = beast.image;
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

int Enemy::hit()
{
    forward_timer = new QTimer();
    forward_timer->setInterval(50);
    QObject::connect(forward_timer, SIGNAL(timeout()), this, SLOT(forward_timer_tick()));
    x_coord = new qreal();
    *x_coord = item->x();
    forward_timer->start();


    backward_timer = new QTimer();
    backward_timer->setInterval(50);
    QObject::connect(backward_timer, SIGNAL(timeout()), this, SLOT(backward_timer_tick()));

    //учесть что надо при атаке, шанс промаха, крита и т.д.
    return attack;
}

void Enemy::get_hit(int amount, QString type)
{
    //кейсим тип, если магический, то одна защита, если физический, то другой
    health -= amount;
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
    item->setPos(item->x() - 10, item->y());

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
    item->setPos(item->x() + 10, item->y());
    if (item->x() >= *x_coord)
    {
        delete x_coord;
        backward_timer->stop();

        if (health > 0)
            emit is_alive();
    }
}
