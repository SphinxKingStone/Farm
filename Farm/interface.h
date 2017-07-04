#ifndef INTERFACE_H
#define INTERFACE_H

#include <QGraphicsView>

class Interface: public QGraphicsView
{
public:
    Interface(QWidget * parent = 0);


private:
    QGraphicsScene * scene;
};

#endif // INTERFACE_H
