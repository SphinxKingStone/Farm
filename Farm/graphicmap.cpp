#include "graphicmap.h"
#include <QDebug>

GraphicMap::GraphicMap(Drop *drop_prt)
{
    drop = drop_prt;
    map_scene = new QGraphicsScene;
    setScene(map_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mapper = new QSignalMapper;
}

void GraphicMap::draw_map(QString location, int x, int y, int width, int height)
{
    qsrand(time(nullptr));

    move(x,y);
    resize (width, height);
    map_scene->setSceneRect(this->rect());
    Location selected_location;
    for (auto it = drop->location_mas.begin(); it != drop->location_mas.end(); ++it)
        if ((*it).name == location)
            selected_location = (*it);

    for (auto it = selected_location.habitat_beasts.begin(); it != selected_location.habitat_beasts.end(); ++it)
        for (int i = 0; i < 3; i++)
        {
            ClickableLabel * label = new ClickableLabel();
            QTimer *timer = new QTimer();

            enemies_container.push_back(map_beast());
            enemies_container.back().label_ptr = label;
            enemies_container.back().timer_ptr = timer;
            enemies_container.back().vecX = qrand() % 5 - 2;
            enemies_container.back().vecY = qrand() % 5 - 2;
            enemies_container.back().speed = (qrand() % 30) + 50;
            enemies_container.back().stop_time = (qrand() % 120) + 80;

            map_scene->addWidget(label);

            label->setPixmap(drop->beast_mas[*it].image.scaled(75,75,Qt::KeepAspectRatio));
            label->setStyleSheet("background: transparent;");
            label->adjustSize();
            label->move((qrand() + x) % int(x + width - label->width() - x), (qrand() + y) % int(y + height - label->height() - y));

            QObject::connect(timer,SIGNAL(timeout()),mapper,SLOT(map()));
            mapper->setMapping(timer, enemies_container.size() - 1);

            timer->start(enemies_container.back().speed);

        }
    QObject::connect(mapper, SIGNAL(mapped(int)), this, SLOT(move_enemy(int)));
}

void GraphicMap::move_enemy(int id)
{
    auto tmp = &enemies_container[id];
    tmp->label_ptr->move(tmp->label_ptr->x() + tmp->vecX, tmp->label_ptr->y() + tmp->vecY);
    tmp->timer_ptr->setInterval(tmp->speed);
    tmp->stop_time--;
    if (tmp->stop_time == 0)
    {
        // рандомим новую скорость передвижения
        tmp->speed = (qrand() % 30) + 50;
        tmp->vecX = qrand() % 5 - 2;
        tmp->vecY = qrand() % 5 - 2;

        // в промежутке от 4 до 10 секунд сработает пауза (80 - 4 сек., 200 - 10), длинной от 1 до 5 сек.
        tmp->stop_time = (qrand() % 120) + 80;
        tmp->timer_ptr->setInterval(qrand() % 4000 + 1000);
    }
    if ((tmp->label_ptr->x() >= this->width() - tmp->label_ptr->width()) || (tmp->label_ptr->y() >= this->height() - tmp->label_ptr->height()))
    {
        tmp->vecX = qrand() % 3 - 2;
        tmp->vecY = qrand() % 3 - 2;

        // уравнивание скоростей
        if ((tmp->vecX == -1) && (tmp->vecY == 0))
            tmp->vecX--;
        else if ((tmp->vecY == -1) && (tmp->vecX == 0))
            tmp->vecY--;
        else if ((tmp->vecX == -1) && (tmp->vecY == -1))
        {
            tmp->vecX--;
            tmp->vecY--;
        }
    }
    if ((tmp->label_ptr->x() <= 0) || (tmp->label_ptr->y() <= 0))
    {
        tmp->vecX = qrand() % 3;
        tmp->vecY = qrand() % 3;

        // уравнивание скоростей
        if ((tmp->vecX == 1) && (tmp->vecY == 0))
            tmp->vecX++;
        else if ((tmp->vecY == 1) && (tmp->vecX == 0))
            tmp->vecY++;
        else if ((tmp->vecX == 1) && (tmp->vecY == 1))
        {
            tmp->vecX++;
            tmp->vecY++;
        }
    }

}
