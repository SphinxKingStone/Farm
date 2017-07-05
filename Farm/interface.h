#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsView>
#include <QPushButton>
#include <QLayout>
#include <QListWidget>

class Interface: public QGraphicsView
{
    Q_OBJECT
public:
    Interface(QWidget * parent = 0);
    ~Interface();
    void show_startWindow();
    void draw_mainScreen();
    void close_mainScreen();

private:
    QGraphicsScene * scene;
    QPushButton * play_buttton;
    QGridLayout * grid_layout;
    QListWidget * location_list;
    QListWidget * beast_list;
    QPushButton * profile_button;
    QPushButton * inventory_button;

private slots:
    void play_bt_click();
    void onLocation_list_item_clicked();
    void onprofile_button_click();
};

#endif // INTERFACE_H
