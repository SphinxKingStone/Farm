#ifndef BEAST_N_DROP_H
#define BEAST_N_DROP_H

#include <QString>


struct beast
{
    int id;
    QString name;
    int drop_chance;
    int rarity;
    int health;
    int attack;
    int xp;
};

struct drop
{
    int id;
    QString name;
    int rarity;
};

#endif // BEAST_N_DROP_H
