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
    inventory = new Inventory(player);
    QObject::connect(inventory, SIGNAL(item_deleted()), this, SLOT(update_inventory()));

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

    labels_map["Player_health"] = new QLabel();
    labels_map["Player_health"]->setText("Здоровье: " + QString::number(player->get_max_health()) + "/" + QString::number(player->get_health()));
    labels_map["Player_health"]->setStyleSheet("font: 16px;");
    grid_layout->addWidget(labels_map["Player_health"],0,0, Qt::AlignCenter | Qt::AlignTop);

    labels_map["Enemy_health"] = new QLabel();
    labels_map["Enemy_health"]->setText("Здоровье: " + QString::number(enemy->get_max_health()) + "/" + QString::number(enemy->get_health()));
    labels_map["Enemy_health"]->setStyleSheet("font: 16px;");
    grid_layout->addWidget(labels_map["Enemy_health"],0,1,Qt::AlignCenter | Qt::AlignTop);

    log = new QListWidget();
    log->setMaximumSize(800,120);
    log->setSelectionMode(QAbstractItemView::NoSelection);
    log->setFocusPolicy(Qt::FocusPolicy::NoFocus);
    grid_layout->addWidget(log,1,0,1,0);

    player->set_item(scene->addPixmap(player->get_image()), 100, 150);
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

void Interface::onProfile_button_click()
{
    close_mainScreen();
    draw_profile();
}

void Interface::onInventory_button_click()
{
    close_mainScreen();

    draw_players_cells();
    draw_inventory_cells();

    draw_Exit_button(exit_inventory_button);
    exit_inventory_button->move(10,540);
    QObject::connect(exit_inventory_button,SIGNAL(clicked(bool)),this, SLOT(onExit_inventory_button_click()));

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

     QObject::connect(play_buttton, SIGNAL(clicked(bool)), this, SLOT(play_bt_click()));
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
    connect(profile_button, SIGNAL(clicked(bool)), this, SLOT(onProfile_button_click()));

    inventory_button = new QPushButton("Инвентарь", nullptr);
    inventory_button->resize(150,60);
    inventory_button->move(profile_button->width() + profile_button->x() + 10, profile_button->y());
    inventory_button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");
    connect(inventory_button, SIGNAL(clicked(bool)), this, SLOT(onInventory_button_click()));

    scene->addWidget(location_list);
    scene->addWidget(beast_list);
    scene->addWidget(profile_button);
    scene->addWidget(inventory_button);
}

bool Interface::draw_Exit_button(QPushButton *&button)
{
    button = new QPushButton("Выход");
    button->setStyleSheet("color: white;"
                           "background-color: lightblue;"
                           "font: 16px;"
                           "font-weight: bold;");
    button->resize(150,50);
    scene->addWidget(button);

    return true;
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

    QLabel *label = new QLabel();
    label->setText("Уровень: " + QString::number(player->get_level()));
    grid_layout->addWidget(label,0,0);
    labels_map["Level"] = label;

    label = new QLabel();
    label->setText("Опыт: " + QString::number(player->get_xp()) + "/" + QString::number(player->get_xp_for_next_lvl()));
    grid_layout->addWidget(label,1,0);
    labels_map["Exp"] = label;

    label = new QLabel();
    label->setText("Здоровье: " + QString::number(player->get_max_health()));
    grid_layout->addWidget(label,2,0);
    labels_map["Health"] = label;

    label = new QLabel();
    label->setText("Атака: " + QString::number(player->get_attack() - round(player->get_attack() * 0.19)) + ".." +
                                  QString::number(player->get_attack() + round(player->get_attack() * 0.19)));
    grid_layout->addWidget(label,3,0);
    labels_map["Attack"] = label;

    label = new QLabel();
    label->setText("Очков навыков: " + QString::number(player->get_skill_point()));
    grid_layout->addWidget(label,0,1,Qt::AlignCenter);
    labels_map["Skill_points"] = label;

    label = new QLabel();
    label->setText("Защита: " + QString::number(player->get_defense()));
    grid_layout->addWidget(label,4,0);
    labels_map["Defense"] = label;

    label = new QLabel();
    label->setText("Ловкость: " + QString::number(player->get_agility()));
    grid_layout->addWidget(label,5,0);
    labels_map["Agility"] = label;

    label = new QLabel();
    label->setText("Концентрация: " + QString::number(player->get_concentration()));
    grid_layout->addWidget(label,6,0);
    labels_map["Concentration"] = label;


    if (player->get_skill_point())
    {
        signalMapper = new QSignalMapper(this);

        QPushButton *button = new QPushButton("+");
        grid_layout->addWidget(button,4,1,Qt::AlignCenter);
        buttons_map["Defense_button"] = button;
        signalMapper->setMapping(button, "Defense_button");
        QObject::connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

        button = new QPushButton("+");
        grid_layout->addWidget(button,5,1,Qt::AlignCenter);
        buttons_map["Agility_button"] = button;
        signalMapper->setMapping(button, "Agility_button");
        QObject::connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

        button = new QPushButton("+");
        grid_layout->addWidget(button,6,1,Qt::AlignCenter);
        buttons_map["Concentration_button"] = button;
        signalMapper->setMapping(button, "Concentration_button");
        QObject::connect(button, SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

        QObject::connect(signalMapper, SIGNAL(mapped(QString)), this, SLOT(onSkill_point_button_click(QString)));
    }

    profile_frame = new QFrame();
    profile_frame->resize(350,400);
    profile_frame->move(10,150);

    scene->addWidget(profile_frame);
    profile_frame->setLayout(grid_layout);

    if (draw_Exit_button(exit_profile_button))
    {
        exit_profile_button->move(10, 10);
        QObject::connect(exit_profile_button,SIGNAL(clicked(bool)),this,SLOT(onExit_profile_button_click()));
    }
}

void Interface::add_log(QString str)
{
    log->addItem(str);
    log->scrollToBottom();
}

void Interface::draw_players_cells()
{
    ClickableLabel * label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(10,150);
    scene->addWidget(label);
    inventory->profile_cells["weapon"] = label;

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(inventory->profile_cells["weapon"]->x(), inventory->profile_cells["weapon"]->y() + inventory->profile_cells["weapon"]->height() + 20);
    scene->addWidget(label);
    inventory->profile_cells["body"] = label;

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(inventory->profile_cells["body"]->x(), inventory->profile_cells["body"]->y() + inventory->profile_cells["body"]->height() + 20);
    scene->addWidget(label);
    inventory->profile_cells["arms"] = label;

    player->set_item(scene->addPixmap(player->get_image()), inventory->profile_cells["weapon"]->x() + inventory->profile_cells["weapon"]->width() + 20, inventory->profile_cells["weapon"]->y());

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(player->get_item()->x() + player->get_item()->boundingRect().width() + 20, inventory->profile_cells["weapon"]->y());
    scene->addWidget(label);
    inventory->profile_cells["shoulders"] = label;

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(inventory->profile_cells["shoulders"]->x(), inventory->profile_cells["shoulders"]->y() + inventory->profile_cells["shoulders"]->height() + 20);
    scene->addWidget(label);
    inventory->profile_cells["legs"] = label;

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(inventory->profile_cells["legs"]->x(), inventory->profile_cells["legs"]->y() + inventory->profile_cells["legs"]->height() + 20);
    scene->addWidget(label);
    inventory->profile_cells["feet"] = label;

    label = new ClickableLabel();
    label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
    label->move(inventory->profile_cells["weapon"]->x() + inventory->profile_cells["shoulders"]->x() / 2, player->get_item()->pos().y() - inventory->profile_cells["weapon"]->height() - 20);
    scene->addWidget(label);
    inventory->profile_cells["head"] = label;
}

void Interface::draw_inventory_cells()
{
    grid_layout = new QGridLayout();
    signalMapper = new QSignalMapper();
    //рисуем клетки
    for (int i = 0; i < 56; i++)
    {
        QLabel * label = new QLabel();
        label->setPixmap(QPixmap(":/images/square.png").scaled(45,45,Qt::KeepAspectRatio));
        grid_layout->addWidget(label,div(i, 7).quot, div(i, 7).rem,Qt::AlignAbsolute);
        inventory->inventory_cells[i] = label;
    }

    //заполняем временный вектор всеми вещами персонажа
    std::vector<Item> tmp = player->get_items();
    int * i = new int(0);
    for (auto itv = tmp.begin(); itv != tmp.end(); itv++)
    {
        add_item_pic((*itv).image, div((*i), 7).quot, div((*i), 7).rem, (*i));
        (*i)++;
    }
    delete i;
    tmp.clear();
    QObject::connect(signalMapper, SIGNAL(mapped(int)), inventory, SLOT(onCell_right_click(int)));

    profile_frame = new QFrame();
    profile_frame->resize(400, 560);
    profile_frame->move(380, 20);

    scene->addWidget(profile_frame);
    profile_frame->setLayout(grid_layout);

    money_label = new QLabel();
    money_label->setText("Золото: " + QString::number(player->get_money()));
    money_label->setStyleSheet("background-color: rgba(255,255,255,0);"
                           "font: 16px;"
                           "font-weight: bold;");
    scene->addWidget(money_label);
    money_label->move(profile_frame->x() - money_label->width() - 10, profile_frame->y());
}

void Interface::update_inventory()
{
    qDebug() << "я тут";
    for (auto it = stupid_pointer.begin(); it != stupid_pointer.end(); it++)
        QObject::disconnect((*it), SIGNAL(rightClicked()), signalMapper, SLOT(map()));

    qDeleteAll(stupid_pointer);
    stupid_pointer.clear();

    std::vector<Item> tmp = player->get_items();
    int * i = new int(0);
    for (auto itv = tmp.begin(); itv != tmp.end(); itv++)
    {
        add_item_pic((*itv).image, div((*i), 7).quot, div((*i), 7).rem, (*i));
        (*i)++;
    }
    delete i;
    tmp.clear();

    money_label->setText("Золото: " + QString::number(player->get_money()));
    money_label->setStyleSheet("background-color: rgba(255,255,255,0);"
                           "font: 16px;"
                           "font-weight: bold;");
    money_label->move(profile_frame->x() - money_label->width() - 10, profile_frame->y());
}

void Interface::add_item_pic(QPixmap image, int row, int column, int i)
{
    ClickableLabel * label = new ClickableLabel();
    label->setPixmap(image);
    grid_layout->addWidget(label,row, column,Qt::AlignAbsolute);
//  делаем вещи кликабельными
    signalMapper->setMapping(label, i);
    QObject::connect(label, SIGNAL(rightClicked()), signalMapper, SLOT(map()));

    stupid_pointer.push_back(label);
}

void Interface::delete_skill_buttons()
{
    QObject::disconnect(buttons_map["Defense_button"], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    QObject::disconnect(buttons_map["Agility_button"], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    QObject::disconnect(buttons_map["Concentration_button"], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
    QObject::disconnect(signalMapper, SIGNAL(mapped(int)), this, SLOT(onSkill_point_button_click(QString)));
    for (auto i = buttons_map.begin(); i != buttons_map.end(); ++i)
        i.value()->deleteLater();

    buttons_map.clear();
    signalMapper->deleteLater();
}

void Interface::update_profile()
{
    labels_map["Skill_points"]->setText("Очков навыков: " + QString::number(player->get_skill_point()));
    labels_map["Defense"]->setText("Защита: " + QString::number(player->get_defense()));
    labels_map["Agility"]->setText("Ловкость: " + QString::number(player->get_agility()));
    labels_map["Concentration"]->setText("Концентрация: " + QString::number(player->get_concentration()));
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
        if (draw_Exit_button(exit_battle_button))
        {
            exit_battle_button->move(scene->width() / 2 - exit_battle_button->width() / 2, scene->height() / 2 - exit_battle_button->height() / 2 - log->height());
            QObject::connect(exit_battle_button,SIGNAL(clicked(bool)),this,SLOT(onExit_battle_button_click()));
        }
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
        {
            add_log("Вам выпало: " + drop->drop_mas[*tmp_id].name);
            player->add_item(drop->drop_mas[*tmp_id]);
        }
        else
            add_log("Вам ничего не выпало");

        delete tmp_id;

        player->increase_xp(enemy->get_xp());

        if (draw_Exit_button(exit_battle_button))
        {
            exit_battle_button->move(scene->width() / 2 - exit_battle_button->width() / 2, scene->height() / 2 - exit_battle_button->height() / 2 - log->height());
            QObject::connect(exit_battle_button,SIGNAL(clicked(bool)),this,SLOT(onExit_battle_button_click()));
        }

    }
}

void Interface::update_health_bar()
{
    labels_map["Player_health"]->setText("Здоровье: " + QString::number(player->get_max_health()) + "/" + QString::number(player->get_health()));
    labels_map["Enemy_health"]->setText("Здоровье: " + QString::number(enemy->get_max_health()) + "/" + QString::number(enemy->get_health()));
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
    QObject::disconnect(exit_battle_button, SIGNAL(clicked(bool)), this, SLOT(onExit_battle_button_click()));
    QObject::disconnect(player, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));
    QObject::disconnect(enemy, SIGNAL(hit_is_done()), this, SLOT(update_health_bar()));
    QObject::disconnect(player, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    QObject::disconnect(enemy, SIGNAL(hit_is_done()), signalMapper, SLOT(map()));
    QObject::disconnect(signalMapper, SIGNAL(mapped(int)), this, SLOT(update_log(int)));
    QObject::disconnect(player, SIGNAL(is_alive()), this, SLOT(enemy_hit()));
    QObject::disconnect(enemy, SIGNAL(is_alive()), this,SLOT(player_hit()));

    delete enemy;
    player->delete_after_battle();
    qDeleteAll(labels_map);
    labels_map.clear();
    log->deleteLater();
    signalMapper->deleteLater();

    grid_layout->deleteLater();
    profile_frame->deleteLater();
    draw_mainScreen();

    exit_battle_button->deleteLater();
}

void Interface::onExit_profile_button_click()
{
    QObject::disconnect(exit_profile_button, SIGNAL(clicked(bool)), this, SLOT(onExit_profile_button_click()));

    qDeleteAll(labels_map);
    labels_map.clear();

    if (player->get_skill_point() > 0)
        delete_skill_buttons();

    grid_layout->deleteLater();
    profile_frame->deleteLater();
    exit_profile_button->deleteLater();
    draw_mainScreen();
}

void Interface::onSkill_point_button_click(QString name)
{
    if (name == "Defense_button")
    {
        player->increase_defense(10);
        player->decrease_skill_points();
    }
    else if (name == "Agility_button")
    {
        player->increase_agility(5);
        player->decrease_skill_points();
    }
    else if (name == "Concentration_button")
    {
        player->increase_concentration(5);
        player->decrease_skill_points();
    }

    if (player->get_skill_point() <= 0)
        delete_skill_buttons();

    update_profile();
}

void Interface::onExit_inventory_button_click()
{
    QObject::disconnect(signalMapper, SIGNAL(mapped(int)), inventory, SLOT(onCell_right_click(int)));
    QObject::disconnect(exit_inventory_button, SIGNAL(clicked(bool)), this, SLOT(onExit_inventory_button_click()));

    for (auto it = stupid_pointer.begin(); it != stupid_pointer.end(); it++)
        QObject::disconnect((*it), SIGNAL(rightClicked()), signalMapper, SLOT(map()));

    profile_frame->deleteLater();
    grid_layout->deleteLater();
    signalMapper->deleteLater();
    player->delete_item();

    qDeleteAll(inventory->inventory_cells);
    inventory->inventory_cells.clear();
    qDeleteAll(inventory->profile_cells);
    inventory->profile_cells.clear();
    qDeleteAll(stupid_pointer);
    stupid_pointer.clear();
    money_label->deleteLater();

    exit_inventory_button->deleteLater();
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
