#include "interface.h"
#include <QDebug>

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
    draw_mainScreen();
    player = new Player();
    variable = new Drop();

    play_buttton->deleteLater();

}

void Interface::onLocation_list_item_clicked()
{
    beast_list->clear();

    switch (location_list->currentRow())
    {
    case 0:
        beast_list->addItem(variable->beast_mas[0].name);
        beast_list->addItem(variable->beast_mas[2].name);
        beast_list->setStyleSheet("background-color: rgba(255, 255, 255, 30%);"
                                  "font: 18px;");
        break;
    case 1:
        beast_list->addItem(variable->beast_mas[1].name);
        beast_list->addItem(variable->beast_mas[2].name);
        beast_list->setStyleSheet("background-image:none;"
                                  "background-color: rgba(255, 255, 255, 30%);"
                                  "font: 18px;");
        break;
    }
}

void Interface::onBeast_list_item_selected()
{
    //ищем итератор по имени существа, которое получаем из выбранной строки в списке
     auto it = std::find_if(variable->beast_mas.begin(), variable->beast_mas.end(), FindByName(beast_list->currentItem()->text()));
     //Если не нашли, то итератор будет указывать на конец вектора, вот и проверяем, нашли ли
     if (it != variable->beast_mas.end())
        enemy = new Enemy(*it);

    close_mainScreen();

    grid_layout = new QGridLayout();

    profile_frame = new QFrame();
    profile_frame->resize(800,600);
    //profile_frame->setStyleSheet("background-image: url(:/images/forest_road.png);");
    scene->addWidget(profile_frame);

    profile_frame->setLayout(grid_layout);

    mas_profile_labels << new QLabel();
    mas_profile_labels.last()->setText("Здоровье: " + QString::number(player->get_max_health()) + "/" + QString::number(player->get_health()));
    mas_profile_labels.last()->setStyleSheet("font: 16px;");
    grid_layout->addWidget(mas_profile_labels.last(),0,0, Qt::AlignCenter | Qt::AlignTop);

    mas_profile_labels << new QLabel();
    mas_profile_labels.last()->setText("Здоровье: " + QString::number(enemy->get_max_health()) + "/" + QString::number(enemy->get_health()));
    mas_profile_labels.last()->setStyleSheet("font: 16px;");
    grid_layout->addWidget(mas_profile_labels.last(),0,1,Qt::AlignCenter | Qt::AlignTop);


    player->set_item(scene->addPixmap(player->get_image()));
    enemy->set_item(scene->addPixmap(enemy->get_image()), player->get_item());
    player->set_enemy_item(enemy->get_item());

    QObject::connect(player, SIGNAL(i_finished()), this, SLOT(update_health_bar()));

    // бой
    battle();
}

void Interface::onprofile_button_click()
{
    close_mainScreen();
    draw_profile();
}

void Interface::show_startWindow()
{
    play_buttton = new QPushButton("Играть", nullptr);
    play_buttton->setFixedSize(300,70);
    play_buttton->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");

    scene->addWidget(play_buttton);
    play_buttton->move(scene->width() / 2 - play_buttton->width() / 2, scene->height() / 2 - play_buttton->height() / 2);

    connect(play_buttton, SIGNAL(clicked(bool)), this, SLOT(play_bt_click()));
}

void Interface::draw_mainScreen()
{
    location_list = new QListWidget();
    location_list->resize(250,500);
    location_list->move(10,80);
    location_list->setStyleSheet("background-color: rgba(255, 255, 255, 30%);"
                                 "font: 18px;");

    //Todo: составить список локаций в отдельном файле и добавлять их одной строкой
    location_list->addItem("Лес");
    location_list->addItem("Тропинка");
    connect(location_list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onLocation_list_item_clicked()));

    beast_list = new QListWidget();
    beast_list->move(location_list->x() + location_list->width() + 30, location_list->y());
    beast_list->resize(scene->width() - beast_list->x() - 10, location_list->height());
    beast_list->setStyleSheet("background-color: rgba(255, 255, 255, 30%);"
                              "font: 18px;");
    connect(beast_list, SIGNAL(itemActivated(QListWidgetItem*)), this, SLOT(onBeast_list_item_selected()));

    profile_button = new QPushButton("Профиль", nullptr);
    profile_button->resize(150,60);
    profile_button->move(10, 10);
    profile_button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");
    connect(profile_button, SIGNAL(clicked(bool)), this, SLOT(onprofile_button_click()));

    inventory_button = new QPushButton("Инвентарь", nullptr);
    inventory_button->resize(150,60);
    inventory_button->move(profile_button->width() + profile_button->x() + 10, profile_button->y());
    inventory_button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");

    scene->addWidget(location_list);
    scene->addWidget(beast_list);
    scene->addWidget(profile_button);
    scene->addWidget(inventory_button);
}

void Interface::close_mainScreen()
{
    location_list->deleteLater();
    beast_list->deleteLater();
    profile_button->deleteLater();
    inventory_button->deleteLater();
}

void Interface::draw_profile()
{
    grid_layout = new QGridLayout();

    mas_profile_labels << new QLabel();
    mas_profile_labels[0]->setText("Уровень: " + QString::number(player->get_level()));
    grid_layout->addWidget(mas_profile_labels[0],0,0,Qt::AlignBaseline);

    mas_profile_labels << new QLabel();
    mas_profile_labels[1]->setText("Опыт: " + QString::number(player->get_xp()) + "/" + QString::number(player->get_xp_for_next_lvl()));
    grid_layout->addWidget(mas_profile_labels[1],1,0,Qt::AlignBaseline);

    mas_profile_labels << new QLabel();
    mas_profile_labels[2]->setText("Здоровье: " + QString::number(player->get_max_health()));
    grid_layout->addWidget(mas_profile_labels[2],2,0,Qt::AlignBaseline);

    mas_profile_labels << new QLabel();
    mas_profile_labels[3]->setText("Атака: " + QString::number(player->get_attack()));
    grid_layout->addWidget(mas_profile_labels[3],3,0,Qt::AlignBaseline);

    for (int i = 0; i <= 3; i++)
    {
        mas_profile_buttons << new QPushButton("+");
        grid_layout->addWidget(mas_profile_buttons[i],i,0,Qt::AlignRight);
    }

    profile_frame = new QFrame();
    profile_frame->resize(400, 500);
    profile_frame->move(0,50);

    scene->addWidget(profile_frame);
    profile_frame->setLayout(grid_layout);
}

void Interface::update_health_bar()
{
    mas_profile_labels[0]->setText("Здоровье: " + QString::number(player->get_max_health()) + "/" + QString::number(player->get_health()));
    mas_profile_labels[1]->setText("Здоровье: " + QString::number(enemy->get_max_health()) + "/" + QString::number(enemy->get_health()));
}

void Interface::battle()
{

    //if (qrand() % ((1 + 1) - 0) + 0)
    if (1 == 1)
    {
        enemy->get_hit(player->hit());
    }
    else
        player->get_hit(enemy->hit());

    // enemy идет вперед, бьет, идет обратно, я иду вперед, бью, иду обратно, так, пока кто - нибудь не умрет.
    // начинаем идти вперед, по таймеру, как только доходим - бьем и идем обратно по таймеру, как только вернулись - останавливаем свой таймер и
    // запускаем таймер движения для соперника, он запустится, только если все живы.

}
