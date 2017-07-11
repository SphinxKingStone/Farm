#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <typeinfo>

class Player: public QObject
{
    Q_OBJECT
public:
    Player();
    ~Player();
    void increase_xp(int amount);
    void increase_lvl();

    void get_hit(int amount, QString type = nullptr);
    int hit();

    int get_level();
    int get_xp();
    int get_max_health();
    int get_health();
    int get_attack();
    int get_xp_for_next_lvl();
    void set_item(QGraphicsPixmapItem * new_item);
    QGraphicsPixmapItem * get_item();
    QPixmap get_image();
private:
    int max_health;
    int health;
    int attack;
    int xp;
    int lvl;
    qreal * x_coord;
    QPixmap image;

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
