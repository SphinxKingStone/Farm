#include "interface.h"

Interface::Interface(QWidget *parent)
{
    scene = new QGraphicsScene(0,0,800,600,nullptr);
    setScene(scene);
}
