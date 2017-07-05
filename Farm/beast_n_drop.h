#ifndef BEAST_N_DROP_H
#define BEAST_N_DROP_H

#include <QString>

typedef std::pair< int, int> level_xp_pair;

struct beast
{
    int id;
    QString name;
    int drop_chance;
    int rarity;
    int health;
    int xp;
};

struct drop
{
    int id;
    QString name;
    int rarity;
};

#endif // BEAST_N_DROP_H
