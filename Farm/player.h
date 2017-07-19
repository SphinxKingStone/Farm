#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <functions_for_persons.h>


class Player: public QObject
{
    Q_OBJECT
public:
    Player();
    ~Player();
    void delete_after_battle();
    void increase_xp(int amount);
    void increase_lvl();

    int get_hit(int amount, QString type = nullptr); // returns: 0 - dodge; -1 - block;
    int hit();
    void restore_health();

    int get_level();
    int get_xp();
    int get_max_health();
    int get_health();
    int get_attack();
    int get_defense();
    int get_agility();
    int get_concentration();
    int get_xp_for_next_lvl();
    int get_skill_point();
    void set_item(QGraphicsPixmapItem * new_item);
    QGraphicsPixmapItem * get_item();
    QPixmap get_image();
    void allocate_timers();
private:
    int max_health;
    int health;
    int defense; // защита дается в десятках от брони, она в процентах поглощает физический урон
    int attack;
    int agility; // шанс уворота
    int concentration; // шанс крита
    int xp;
    int lvl;
    int skill_point;

    qreal * x_coord;
    QPixmap image;
    int * animation_speed;
    qreal * pixel_step;

    QGraphicsPixmapItem * item;

    QTimer * forward_timer;
    QTimer * backward_timer;
private slots:
    void forward_timer_tick();
    void backward_timer_tick();

signals:
    void hit_is_done();
    void is_alive();

};


#endif // PLAYER_H
