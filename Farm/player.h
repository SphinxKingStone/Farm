#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player
{
public:
    Player();
    void increase_xp(int amount);
    void increase_lvl();
    int get_level();
    int get_xp();
    int get_health();
    int get_attack();
    int get_xp_for_next_lvl();
private:
    int health;
    int attack;
    int xp;
    int lvl;
};


#endif // PLAYER_H
