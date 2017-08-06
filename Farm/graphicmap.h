#ifndef GRAPHICMAP_H
#define GRAPHICMAP_H

#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "drop.h"
#include "beast_n_drop.h"
#include <QLabel>
#include <QTimer>
#include "clickablelabel.h"
#include <QSignalMapper>

struct map_beast
{
    ClickableLabel *label_ptr;
    QTimer *timer_ptr;
    int vecX;
    int vecY;
    int speed;
    int stop_time;
};

class GraphicMap: public QGraphicsView
{
    Q_OBJECT
public:
    GraphicMap(Drop * drop_prt);
    void draw_map(QString location, int x, int y, int width, int height);

private:
    QGraphicsScene * map_scene;
    Drop * drop;
    QSignalMapper * mapper;

    QList<map_beast> enemies_container;

public slots:
    void move_enemy(int id);

};

#endif // GRAPHICMAP_H
