#include "functions_for_persons.h"


bool avoid(int base_value, double min_value)
{
    double chance = static_cast<double>(qrand()) / RAND_MAX;
    chance = (min_value + (*chance) * (100.0 - min_value));
    double my_chance = base_value * min_value;

    return my_chance >= chance;
}
