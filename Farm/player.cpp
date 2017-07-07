#include "player.h"
#include <utility>

std::vector<std::pair<int, int>> level_xp;

Player::Player()
{
    //Todo: инициализировать не в конструкторе, а как - то единожды, при запуске программы
    for (int i = 0; i < 100; i++)
    {
        level_xp.insert(level_xp.end(), std::make_pair(i, i * 50));
    }

    max_health = 20;
    attack = 2;
    xp = 0;
    lvl = 1;

    //Вызывает libpng warning: iCCP: known incorrect sRGB profile
    image = (QPixmap(":/images/main_hero.png"));
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
    max_health += 10;
    attack += 1;
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
    return health;
}

int Player::get_attack()
{
    return attack;
}

int Player::get_xp_for_next_lvl()
{
    return level_xp[lvl].second;
}

QPixmap Player::get_image()
{
    return image;
}
