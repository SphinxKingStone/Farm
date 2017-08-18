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
#include <QGridLayout>
#include <QPushButton>

struct map_beast
{
    int beast_id;
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
    GraphicMap(Drop * drop_prt, int x, int y, int width, int height);
    ~GraphicMap();
    void fill_map(QString location);

private:
    void clear_map();

    QGraphicsScene * map_scene;
    const Drop * drop;
    QSignalMapper * timer_mapper;
    QSignalMapper *  double_click_mapper;
    QSignalMapper *  click_mapper;

    QList<map_beast> enemies_container;

public slots:
    void move_enemy(int id);
    void on_enemy_double_click(int container_id);
    void on_enemy_click(int container_id);

signals:
    void beast_clicked(Beast beast);
    void beast_selected(Beast beast);

};

#endif // GRAPHICMAP_H
