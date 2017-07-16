#ifndef BEAST_N_DROP_H
#define BEAST_N_DROP_H

#include <QString>
#include <QPixmap>


struct Beast
{
    int id;
    QString name;
    int drop_chance;
    int rarity;
    int health;
    int defense;
    int attack;
    int xp;
    int lvl;
    QPixmap image;
};

//Для поиска по имени для std::find_if
struct FindByName {
    const QString name;
    FindByName(const QString& name) : name(name) {}
    bool operator()(const Beast& j) const {
        return j.name == name;
    }
};

struct drop
{
    int id;
    QString name;
    int rarity;
};

#endif // BEAST_N_DROP_H
