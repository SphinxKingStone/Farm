#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include "beast_n_drop.h"
#include <QTimer>
#include <QObject>


class Enemy: public QObject
{
    Q_OBJECT
public:
    Enemy(Beast beast);
    QPixmap get_image();
    int get_max_health();
    int get_health();

    int hit();
    void get_hit (int amount, QString type = nullptr);

    void set_item(QGraphicsPixmapItem * new_item, QGraphicsPixmapItem * players_item);
    QGraphicsPixmapItem * get_item();
private:
    int max_health;
    int health;
    int attack;
    int xp_reward;
    int lvl;
    QPixmap image;

    QGraphicsPixmapItem * item;

    QTimer * forward_timer;
    QTimer * backward_timer;
private slots:
    void forward_timer_tick();
    void backward_timer_tick();
};

#endif // ENEMY_H
