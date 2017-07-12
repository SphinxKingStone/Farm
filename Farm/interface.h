#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsView>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>
#include <QLabel>
#include <QFrame>
#include <player.h>
#include "drop.h"
#include "enemy.h"
#include <QTimer>
#include <QSignalMapper>

class Interface: public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    ~Interface();
    void show_startWindow();
    void draw_mainScreen();
    void draw_Exit_battle_button();
    void close_mainScreen();
    void draw_profile();
    void add_log(QString str);

    Player * player;
    Drop * drop_class_variable;
    Enemy * enemy;

    int test = 10;

private:
    QGraphicsScene * scene;
    QPushButton * play_buttton;
    QGridLayout * grid_layout;
    QListWidget * location_list;
    QListWidget * beast_list;
    QPushButton * profile_button;
    QPushButton * inventory_button;
    QFrame * profile_frame;
    QTimer * timer;
    QListWidget * log;
    QSignalMapper * signalMapper;
    QPushButton * exit_battle_button;

    int * hit_value;

    QList<QLabel*> mas_profile_labels;
    QList<QPushButton*> mas_profile_buttons;

private slots:
    void play_bt_click();
    void onLocation_list_item_clicked();
    void onBeast_list_item_selected();
    void onprofile_button_click();
    void battle();
    void update_health_bar();
    void update_log(int players_hit);
    void onExit_battle_button_click();

    void player_hit();
    void enemy_hit();
};


#endif // INTERFACE_H
