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
#include "clickablelabel.h"
#include "inventory.h"
#include "beast_n_drop.h"
#include "graphicmap.h"


class Interface: public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    ~Interface();
    void show_startWindow();
    void draw_mainScreen();
    bool draw_Exit_button(QPushButton *&button);
    bool close_mainScreen();
    void draw_profile();
    void add_log(QString str);
    void draw_players_cells();
    void draw_inventory_cells();
    void draw_inventory_stats();
    void drawInfoFrame(Item item);
    void draw_equppied_items();
    void draw_items();

    void add_item_pic(QGridLayout * layout, QPixmap image, int row, int column, int i = 0);

    //QString declension(QString name, char sex, bool isName); Надо будет доработать

    Player * player;
    Drop * drop;
    Enemy * enemy;
    Inventory * inventory;

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
    QSignalMapper * entersMapper;
    QPushButton * exit_battle_button;
    QPushButton * exit_profile_button;
    QPushButton * exit_inventory_button;
    QLabel * money_label;
    QGridLayout * players_layout;
    QGraphicsView * players_view;
    QVBoxLayout * info_layout;
    QGraphicsView * info_view;
    QGridLayout * inventory_layout;
    QGraphicsView * inventory_view;

    int * hit_value;

    QMap<QString, QLabel*> labels_map;
    QMap<QString, QPushButton*> buttons_map;
    QMap<QString, ClickableLabel*> clickable_labels_map;

    void delete_skill_buttons();
    void update_profile();
    void delete_inventory_stats();

    QList<ClickableLabel*> stupid_pointer;
    QList<QLabel*> info_labels;
    QList<QLabel*> inventory_stats_labels;

private slots:
    void play_bt_click();
    void onLocation_list_item_clicked();
    void onBeast_list_item_selected();
    void onProfile_button_click();
    void onInventory_button_click();
    void battle();
    void update_health_bar();
    void update_log(int players_hit);
    void update_inventory();
    void onExit_battle_button_click();
    void onExit_profile_button_click();
    void onSkill_point_button_click(QString name);
    bool onExit_inventory_button_click();
    void onEntered(int id);
    void onEntered(QString place);
    void onLeft();

    void player_hit();
    void enemy_hit();
};

QPair<int,int> gridPosition(QWidget * widget); //получить ряд и столб виджета из layout, в случае ошибки вернет -1 -1


#endif // INTERFACE_H
