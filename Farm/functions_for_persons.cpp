#include "functions_for_persons.h"


bool avoid(int base_value, double min_value)
{
    double * chance = new double();
    double * my_chance = new double();
    *chance = (double)qrand() / RAND_MAX;
    *chance = (min_value + (*chance) * (100.0 - min_value));
    *my_chance = base_value * min_value;

    if (*my_chance >= *chance)
    {
        delete my_chance;
        delete chance;
        return true;
    }
    delete my_chance;
    delete chance;
    return false;
}
