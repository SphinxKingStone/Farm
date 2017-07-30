#ifndef DROP_H
#define DROP_H

#include <vector>
#include "beast_n_drop.h"


//Временный класс?
class Drop
{
public:
    Drop();

    void fill_beast_mas(std::vector<Beast> &mas);
    void fill_drop_mas(std::vector<Item> &mas);
    void fill_location_mas(std::vector<Location> &mas);
    int simulate_drop(int beast_type);

    ~Drop();

    std::vector<Beast> beast_mas;
    std::vector<Item> drop_mas;
    std::vector<Item> tmp_drop;
    std::vector<Location> location_mas;
};

#endif // DROP_H
