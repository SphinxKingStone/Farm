#include "interface.h"

Interface::Interface(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    scene = new QGraphicsScene(0,0,800,600,nullptr);

    scene->setBackgroundBrush(QBrush(QImage(":/images/green_bg.jpg")));

    setScene(scene);

    show_startWindow();
}

Interface::~Interface()
{
    delete scene;
}

void Interface::play_bt_click()
{
    play_bt->deleteLater();
    draw_mainScreen();
}

void Interface::show_startWindow()
{
    play_bt = new QPushButton("Играть", nullptr);
    play_bt->setFixedSize(300,70);
    play_bt->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font : 16px;"
                           "font-weight:bold;");

    scene->addWidget(play_bt);
    play_bt->move(scene->width() / 2 - play_bt->width() / 2, + scene->height() / 2 - play_bt->height() / 2);

    connect(play_bt, SIGNAL(clicked(bool)), this, SLOT(play_bt_click()));
}

void Interface::draw_mainScreen()
{
    list = new QListWidget();
    list->resize(250,500);
    list->move(10,50);

    list->addItem("Лес");

    scene->addWidget(list);
}
