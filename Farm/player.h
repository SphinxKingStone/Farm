#ifndef PLAYER_H
#define PLAYER_H

#include "beast_n_drop.h"

class Player
{
public:
    Player();
    void increase_xp(int amount);
    void increase_lvl();
private:
    int health;
    int attack;
    int xp;
    int lvl;
};


#endif // PLAYER_H
