#include "graphicmap.h"
#include <QDebug>

GraphicMap::GraphicMap(Drop *drop_prt, int x, int y, int width, int height)
{
    drop = drop_prt;
    map_scene = new QGraphicsScene;
    setScene(map_scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timer_mapper = new QSignalMapper;
    double_click_mapper = new QSignalMapper;
    click_mapper = new QSignalMapper;

    move(x,y);
    resize (width, height);
    map_scene->setSceneRect(this->rect());
}

GraphicMap::~GraphicMap()
{
    map_scene->deleteLater();
    timer_mapper->deleteLater();
    double_click_mapper->deleteLater();
    clear_map();
}

void GraphicMap::fill_map(QString location)
{
    clear_map();
    qsrand(time(nullptr));

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
            enemies_container.back().beast_id = *it;
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
            label->move((qrand() + this->x()) % int(this->x() + this->width() - label->width() - this->x()),
                        (qrand() + this->y()) % int(this->y() + this->height() - label->height() - this->y()));
            double_click_mapper->setMapping(label,enemies_container.size() - 1);
            QObject::connect(label,SIGNAL(doubleClicked()),double_click_mapper,SLOT(map()));
            click_mapper->setMapping(label,enemies_container.size() - 1);
            QObject::connect(label,SIGNAL(clicked()),click_mapper,SLOT(map()));

            timer_mapper->setMapping(timer, enemies_container.size() - 1);
            QObject::connect(timer,SIGNAL(timeout()),timer_mapper,SLOT(map()));

            timer->start(enemies_container.back().speed);

        }
    QObject::connect(timer_mapper, SIGNAL(mapped(int)), this, SLOT(move_enemy(int)));
    QObject::connect(double_click_mapper, SIGNAL(mapped(int)), this, SLOT(on_enemy_double_click(int)));
    QObject::connect(click_mapper, SIGNAL(mapped(int)), this, SLOT(on_enemy_click(int)));
}

void GraphicMap::clear_map()
{
    for (auto it = enemies_container.begin(); it != enemies_container.end(); ++it)
    {
        QObject::disconnect((*it).label_ptr,SIGNAL(doubleClicked()),double_click_mapper,SLOT(map()));
        QObject::disconnect((*it).timer_ptr,SIGNAL(timeout()),timer_mapper,SLOT(map()));
        (*it).label_ptr->deleteLater();
        (*it).timer_ptr->deleteLater();
    }
    enemies_container.clear();

    QObject::disconnect(timer_mapper, SIGNAL(mapped(int)), this, SLOT(move_enemy(int)));
    QObject::disconnect(double_click_mapper, SIGNAL(mapped(int)), this, SLOT(on_enemy_double_click(int)));
    QObject::disconnect(click_mapper, SIGNAL(mapped(int)), this, SLOT(on_enemy_click(int)));
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

void GraphicMap::on_enemy_double_click(int container_id)
{
    emit beast_selected(drop->beast_mas[enemies_container[container_id].beast_id]);
}

void GraphicMap::on_enemy_click(int container_id)
{
    emit beast_clicked(drop->beast_mas[enemies_container[container_id].beast_id]);
}
