#include "gamesave.h"

GameSave::GameSave()
{

}

GameSave::saveProgress(Player *player)
{
    QFile file("save.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << QString::number(player->get_max_health()) << "\n";
        stream << QString::number(player->get_defense()) << "\n";
        stream << QString::number(player->get_attack()) << "\n";
        stream << QString::number(player->get_agility()) << "\n";
        stream << QString::number(player->get_concentration()) << "\n";
        stream << QString::number(player->get_xp()) << "\n";
        stream << QString::number(player->get_level()) << "\n";
        stream << QString::number(player->get_skill_point()) << "\n";

        QMap<int, Item> items = player->get_items();
        for (int i = 0; i < items.size(); i++)
            stream << items[i].id << "\n";
        stream << "items_end" << "\n";

        QMap<QString, Item> equipped_items = player->get_equipped_items();
        for (auto it = equipped_items.begin(); it != equipped_items.end(); ++it)
        {
            stream << it.key() << "\n";
            stream << (*it).id << "\n";
        }
        stream << "equipped_items_end" << "\n";
        stream << player->get_money() << "\n";

        file.close();
    }
}

int read_n_chop(QFile *file)
{
    QString str = file->readLine();
    return str.left(str.length() - 1).toInt();
}

GameSave::loadProgress(Player *player, Drop *drop)
{
    QFile file("save.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        player->set_max_health(read_n_chop(&file));
        player->set_defense(read_n_chop(&file));
        player->set_attack(read_n_chop(&file));
        player->set_agility(read_n_chop(&file));
        player->set_concentration(read_n_chop(&file));
        player->set_xp(read_n_chop(&file));
        player->set_lvl(read_n_chop(&file));
        player->set_skill_points(read_n_chop(&file));

        QString str;
        while (true)
        {
            str = file.readLine();
            str = str.left(str.length() - 1);
            if (str == "items_end")
                break;

            player->add_item(drop->drop_mas[str.toInt()]);
        }
        while (true)
        {
            str = file.readLine();
            if (str == "equipped_items_end\n")
                break;

            QString tmp = file.readLine();
            int i = tmp.left(tmp.length() - 1).toInt();
            player->equip_item(str.left(str.length() - 1), drop->drop_mas[i]);
        }
        str = file.readLine();
        player->set_money(str.left(str.length() - 1).toInt());
    }
}
