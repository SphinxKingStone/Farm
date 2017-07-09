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
    return health;
}

int Enemy::hit()
{
    //учесть что надо при атаке, шанс промаха, крита и т.д.
    forward_timer->setInterval(50);
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

}

void Enemy::backward_timer_tick()
{

}
