#include "inventory.h"
#include <QDebug>

Inventory::Inventory()
{

}

Inventory::onCell_click()
{
    qDebug() << "click";
}

Inventory::onCell_right_click(int id)
{
    qDebug() << "right click";
    qDebug() << id;
    QMenu * menu = new QMenu;

    QAction * sell = menu->addAction(QIcon(":/images/coin.png"), "Продать");
    connect(sell, SIGNAL(triggered(bool)), this, SLOT(onCell_click()));

    QAction * throw_out = menu->addAction(QIcon(":/images/trash_can.png"),"Выкинуть");
    connect(throw_out, SIGNAL(triggered(bool)), this, SLOT(onCell_click()));

    menu->setStyleSheet("color: white;"
                        "background-color: rgba(255,255,255,100);");
    menu->exec(cells[0]->mapToGlobal(cells[id]->pos()));
}
