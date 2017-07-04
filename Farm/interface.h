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

private:
    QGraphicsScene * scene;
    QPushButton * play_bt;
    QGridLayout * grid_layout;
    QListWidget * list;

private slots:
    void play_bt_click();
};

#endif // INTERFACE_H
