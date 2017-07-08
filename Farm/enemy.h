#ifndef ENEMY_H
#define ENEMY_H

#include <QPixmap>
#include "beast_n_drop.h"


class Enemy
{
public:
    Enemy(Beast beast);
    QPixmap get_image();
    int get_max_health();
    int get_health();
private:
    int max_health;
    int health;
    int attack;
    int xp_reward;
    int lvl;
    QPixmap image;
};

#endif // ENEMY_H
