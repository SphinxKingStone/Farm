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
