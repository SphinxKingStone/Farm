#ifndef GAME_H
#define GAME_H

#include "interface.h"
#include "player.h"
#include "inventory.h"

class Game
{
public:
    Game();

private:
    Player * player;
    Interface * interface;
    Inventory * Inventory;
};

#endif // GAME_H
