#ifndef GAMESAVE_H
#define GAMESAVE_H

#include "player.h"
#include <QFile>
#include <QTextStream>
#include "drop.h"


class GameSave
{
public:
    GameSave();
    static saveProgress(Player * player);
    static loadProgress(Player * player, Drop * drop);
};

#endif // GAMESAVE_H
