#include <QApplication>
#include "interface.h"
#include "drop.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);;


    Interface * window = new Interface;
    window->show();


    return a.exec();
}
