#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include "beast_n_drop.h"
#include <QTimer>
#include <QObject>
#include <typeinfo>
#include <functions_for_persons.h>


class Enemy: public QObject
{
    Q_OBJECT
public:
    Enemy(Beast beast);
    ~Enemy();

    int get_beast_id();
    QPixmap get_image();
    int get_max_health();
    int get_health();
    int get_attack();
    int get_xp();
    QString get_name();

    int hit();
    int get_hit(int amount, QString type = nullptr); // returns: 0 - dodge; -1 - block;

    void set_item(QGraphicsPixmapItem * new_item, QGraphicsPixmapItem * players_item);
    QGraphicsPixmapItem * get_item();
private:
    int beast_id;
    int max_health;
    int health;
    int defense;
    int agility;
    int concentration;
    QString name;
    int attack;
    int xp_reward;
    int lvl;
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

#endif // ENEMY_H
