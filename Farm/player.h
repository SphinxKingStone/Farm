#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QGraphicsPixmapItem>

class Player
{
public:
    Player();
    void increase_xp(int amount);
    void increase_lvl();
    void get_damage(int amount);
    int get_level();
    int get_xp();
    int get_max_health();
    int get_health();
    int get_attack();
    int get_xp_for_next_lvl();
    QPixmap get_image();
private:
    int max_health;
    int health;
    int attack;
    int xp;
    int lvl;
    QPixmap image;

};


#endif // PLAYER_H
