#ifndef BEAST_N_DROP_H
#define BEAST_N_DROP_H

#include <QString>
#include <QMap>
#include <QPixmap>


struct Beast
{
    int id;
    QString name;
    int drop_chance;
    int rarity;
    int health;
    int defense;
    int agility;
    int concentration;
    int attack;
    int xp;
    int lvl;
    QPixmap image;
};

//Для поиска по имени для std::find_if
struct FindByName
{
    const QString name;
    FindByName(const QString& name) : name(name) {}
    bool operator()(const Beast& j) const
    {
        return j.name == name;
    }
};

struct Item
{
    int id;
    QString name;
    QString type;
    int rarity;
    QPixmap image;
    int cost;
    QMap<QString, int> stats;
};

struct Location
{
    QString name;
    std::vector<int> habitat_beasts;
};


#endif // BEAST_N_DROP_H
