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

class Interface: public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    ~Interface();
    void show_startWindow();
    void draw_mainScreen();
    void close_mainScreen();
    void draw_profile();

    Player * player;
    Drop * variable;
    Enemy * enemy;

private:
    QGraphicsScene * scene;
    QPushButton * play_buttton;
    QGridLayout * grid_layout;
    QListWidget * location_list;
    QListWidget * beast_list;
    QPushButton * profile_button;
    QPushButton * inventory_button;
    QFrame * profile_frame;

    QList<QLabel*> mas_profile_labels;
    QList<QPushButton*> mas_profile_buttons;


private slots:
    void play_bt_click();
    void onLocation_list_item_clicked();
    void onBeast_list_item_selected();
    void onprofile_button_click();
};

#endif // INTERFACE_H
