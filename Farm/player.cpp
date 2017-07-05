#include "player.h"

level_xp_pair level_xp[3];

Player::Player()
{
    //Todo: инициализировать не в конструкторе, а как - то единожды, при запуске программы
    level_xp[0].first = 1;
    level_xp[0].second = 0;
    level_xp[1].first = 2;
    level_xp[1].second = 50;
    level_xp[2].first = 3;
    level_xp[2].second = 200;
    level_xp[3].first = 4;
    level_xp[3].second = 500;

    health = 20;
    attack = 2;
    xp = 0;
    lvl = 1;
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
    health += 10;
    attack += 1;
}
