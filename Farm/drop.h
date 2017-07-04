#ifndef DROP_H
#define DROP_H

#include <QGraphicsView>
#include <vector>
#include <QListWidget>
#include "beast_n_drop.h"

class Drop: public QGraphicsView
{
public:
    Drop(QWidget * parent=0);
    QGraphicsScene * scene;
    QListWidget * list;

    void fill_beast_mas(std::vector<beast> &mas);
    void fill_drop_mas(std::vector<drop> &mas);
    void simulate_drop();

    ~Drop();

private:
        std::vector<beast> beast_mas;
        std::vector<drop> drop_mas;
        std::vector<drop> tmp_drop;
};

#endif // DROP_H
