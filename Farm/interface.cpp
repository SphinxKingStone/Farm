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
    drop = new Drop();

    play_buttton->deleteLater();

}

void Interface::onLocation_list_item_clicked()
{
    beast_list->clear();

    switch (location_list->currentRow())
    {
    case 0:
        beast_list->addItem(drop->beast_mas[0].name + " (" + QString::number(drop->beast_mas[0].lvl) + ")");
        beast_list->addItem(drop->beast_mas[2].name + " (" + QString::number(drop->beast_mas[2].lvl) + ")");
        beast_list->setStyleSheet("background-color: rgba(255, 255, 255, 30%);"
                                  "font: 18px;");
        break;
    case 1:
        beast_list->addItem(drop->beast_mas[1].name + " (" + QString::number(drop->beast_mas[1].lvl) + ")");
        beast_list->addItem(drop->beast_mas[2].name + " (" + QString::number(drop->beast_mas[2].lvl) + ")");
        beast_list->setStyleSheet("background-color: rgba(255, 255, 255, 30%);"
                                  "font: 18px;");
        break;
    }
}

void Interface::onBeast_list_item_selected()
{
     //ищем итератор по имени существа (строка, пока не встретится пробле), которое получаем из выбранной строки в списке
     auto it = std::find_if(drop->beast_mas.begin(), drop->beast_mas.end(), FindByName(beast_list->currentItem()->text().split(" ").at(0)));
     //Если не нашли, то итератор будет указывать на конец вектора, вот и проверяем, нашли ли
     if (it != drop->beast_mas.end())
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

    log = new QListWidget();
    log->setMaximumSize(800,120);
    log->setSelectionMode(QAbstractItemView::NoSelection);
    log->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    grid_layout->addWidget(log,1,0,1,0);

    player->set_item(scene->addPixmap(player->get_image()));
    enemy->set_item(scene->addPixmap(enemy->get_image()), player->get_item());

    QObject::connect(player, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));
    QObject::connect(enemy, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));

    // Так можно в слот передать параметры
    signalMapper = new QSignalMapper(this);
    signalMapper->setMapping(player, 1); // если класс player, то передадим 1
    signalMapper->setMapping(enemy, 0); // если класс enemy, то передадим 0
    // Класс player дает сигнал, сигнал маппер принимает его, и раз это от player, то записывает 1
    QObject::connect(player, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    QObject::connect(enemy, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    // Только что в маппер записалась единица (int) и на этот сигнал мы вызывам слот update_log и передаем туда эту единицу
    QObject::connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(update_log(int)));


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

void Interface::draw_Exit_battle_button()
{
    exit_battle_button = new QPushButton("Выход");
    exit_battle_button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");
    exit_battle_button->resize(150,50);
    scene->addWidget(exit_battle_button);
    exit_battle_button->move(scene->width() / 2 - exit_battle_button->width() / 2, scene->height() / 2 - exit_battle_button->height() / 2 - log->height());
    QObject::connect(exit_battle_button,SIGNAL(clicked(bool)),this,SLOT(onExit_battle_button_click()));
}

void Interface::draw_Exit_profile_button()
{
    exit_profile_button = new QPushButton("Выход");
    exit_profile_button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");
    exit_profile_button->resize(150,50);
    scene->addWidget(exit_profile_button);
    exit_profile_button->move(10, 10);
    QObject::connect(exit_profile_button,SIGNAL(clicked(bool)),this,SLOT(onExit_profile_button_click()));
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
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Уровень: " + QString::number(player->get_level()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],0,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Опыт: " + QString::number(player->get_xp()) + "/" + QString::number(player->get_xp_for_next_lvl()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],1,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Здоровье: " + QString::number(player->get_max_health()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],2,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Атака: " + QString::number(player->get_attack() - round(player->get_attack() * 0.19)) + ".." +
                                                               QString::number(player->get_attack() + round(player->get_attack() * 0.19)));


    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],3,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Очков навыков: " + QString::number(player->get_skill_point()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],0,1,Qt::AlignCenter);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Очков навыков: " + QString::number(player->get_skill_point()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],0,1,Qt::AlignCenter);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Защита: " + QString::number(player->get_defense()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],4,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Ловкость: " + QString::number(player->get_agility()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],5,0);

    mas_profile_labels << new QLabel();
    mas_profile_labels[mas_profile_labels.size() - 1]->setText("Концентрация: " + QString::number(player->get_concentration()));
    grid_layout->addWidget(mas_profile_labels[mas_profile_labels.size() - 1],6,0);

    if (player->get_skill_point())
        for (int i = 0; i < mas_profile_labels.size() - 3; i++)
        {
            mas_profile_buttons << new QPushButton("+");
            grid_layout->addWidget(mas_profile_buttons[i],i+1,1,Qt::AlignCenter);
        }

    profile_frame = new QFrame();
    profile_frame->resize(350,400);
    profile_frame->move(10,150);

    scene->addWidget(profile_frame);
    profile_frame->setLayout(grid_layout);

    draw_Exit_profile_button();
}

void Interface::add_log(QString str)
{
    log->addItem(str);
    log->scrollToBottom();
}

/*
// С полом будут проблемы у слов: тень, бродяга, дятел, пень, конь и т.д.
QString Interface::declension(QString name, char sex,  bool isName)
{
    if (isName)
    {
        if ((name.right(1) == "а") || (name.right(1) == "я"))
        {
            name = name.left(name.length() - 1);
            name += "е";
        }
        else if (name.right(1) == "о")
        {
            name = name.left(name.length() - 1);
            name += "у";
        }
        else if ((name.right(1) == "ь") && (sex == "м"))
        {
            name = name.left(name.length() - 1);
            name += "ю";
        }
        else if ((name.right(1) == "ь") && (sex == "ж"))
        {
            name = name.left(name.length() - 1);
            name += "и";
        }
        else
        {
            name += "у";
        }
        return name;
    }
    else
    {
        if (((name.right(1) == "а") || (name.right(1) == "я")) && (sex == "ж"))
        {
            return ("нанесла");
        }
        else if (name.right(1) == "о")
        {
            return ("нанесло");
        }
        else
        {
            return ("нанёс");
        }
    }

    return ("Ошибка склонения");

}
*/

void Interface::player_hit()
{
    if (player->get_health() > 0)
    {
        hit_value = new int();
        *hit_value = enemy->get_hit(player->hit());
    }
    else
    {
        add_log("Игрок умер");
        player->restore_health();
        draw_Exit_battle_button();
    }
}

void Interface::enemy_hit()
{
    if (enemy->get_health() > 0)
    {
        hit_value = new int();
        *hit_value = player->get_hit(enemy->hit());
    }
    else
    {
        add_log(enemy->get_name() + " умер");
        player->restore_health();
        int * tmp_id = new int(drop->simulate_drop(enemy->get_beast_id()));
//        нельзя написать if (int * tmp_id = new int(drop_class_variable->simulate_drop(enemy->get_beast_id()))), потому что будет возвращаться указатель на выделенную
//        память, а не значение, которое мы присвоили, а вот if (int tmp = get_number()) написать можно, там будет значение tmp возвращаться.
//        Только что узнал об этом, но запишу, чтобы лучше запомнилось, хоть это и гуглится по первой ссылке

        // Число 9999 значит, что ничего не выпало, не использутся ноль, потому что для его использования пришлось бы добавить фиктивную, нулевую запись,
        // в массив с предметами, как обойти это по красивому у меня идей нет.
        if (*tmp_id != 9999)
            add_log("Вам выпало: " + drop->drop_mas[*tmp_id].name);
        else
            add_log("Вам ничего не выпало");

        delete tmp_id;

        player->increase_xp(enemy->get_xp());

        draw_Exit_battle_button();

    }
}

void Interface::update_health_bar()
{
    mas_profile_labels[0]->setText("Здоровье: " + QString::number(player->get_max_health()) + "/" + QString::number(player->get_health()));
    mas_profile_labels[1]->setText("Здоровье: " + QString::number(enemy->get_max_health()) + "/" + QString::number(enemy->get_health()));
}

//TODO: нормально склонять имена противников и слово "нанёс"
void Interface::update_log(int players_hit)
{
    if (players_hit == 1)
    {
        if (*hit_value > 0)
        {
            if (*hit_value <= round(player->get_attack() * 1.19))
                add_log("Игрок нанёс " + enemy->get_name() + " " + QString::number(*hit_value) + " ед. урона");
            else
                add_log("Игрок нанёс критическим ударом " + enemy->get_name() + " " + QString::number(*hit_value) + " ед. урона");
        }
        else if (*hit_value == 0)
            add_log( enemy->get_name() + " увернулся от удара");
        else if (*hit_value == -1)
            add_log( enemy->get_name() + " заблокировал удар");
    }
    else
    {
        if (*hit_value > 0)
        {
            if (*hit_value <= round(enemy->get_attack() * 1.19))
                add_log(enemy->get_name() + " нанёс Игроку " + QString::number(*hit_value) + " ед. урона");
            else
                add_log(enemy->get_name() + " нанёс критическим ударом Игроку " + QString::number(*hit_value) + " ед. урона");
        }
        else if (*hit_value == 0)
            add_log("Игрок увернулся от удара");
        else if (*hit_value == -1)
            add_log("Игрок заблокировал удар");
    }

    delete hit_value;
}

void Interface::onExit_battle_button_click()
{
    disconnect(exit_battle_button, SIGNAL(clicked(bool)), this, SLOT(onExit_battle_button_click()));
    disconnect(player, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));
    disconnect(enemy, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));
    disconnect(player, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    disconnect(enemy, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    disconnect(signalMapper, SIGNAL(mapped(int)), this, SLOT(update_log(int)));
    disconnect(player, SIGNAL(is_alive()), this, SLOT(enemy_hit()));
    disconnect(enemy, SIGNAL(is_alive()), this,SLOT(player_hit()));

    enemy->deleteLater();
    player->delete_after_battle();
    mas_profile_labels.clear();
    log->deleteLater();
    signalMapper->deleteLater();

    grid_layout->deleteLater();
    profile_frame->deleteLater();
    draw_mainScreen();

    exit_battle_button->deleteLater();
}

void Interface::onExit_profile_button_click()
{
    disconnect(exit_profile_button, SIGNAL(clicked(bool)), this, SLOT(onExit_profile_button_click()));
    mas_profile_labels.clear();
    mas_profile_buttons.clear();
    grid_layout->deleteLater();
    profile_frame->deleteLater();
    draw_mainScreen();
}

void Interface::battle()
{
    player->allocate_timers();

    //Если враг жив, то его бьет игрок, и наоборот
    connect(player, SIGNAL(is_alive()), this, SLOT(enemy_hit()));
    connect(enemy, SIGNAL(is_alive()), this,SLOT(player_hit()));

    //Если 1, то первым бьет персонаж, если 0, то противник. Можно будет учесть уровни и удачу при рандоме
    qsrand(time(nullptr));
    if (qrand() % ((1 + 1) - 0) + 0)
    {
        player_hit();
    }
    else
    {
        enemy_hit();
    }

}
