#ifndef ENTITY_H
#define ENTITY_H

#include "definitions.h"


class Entity
{
private:
public:

    double x = 0.0;
    double y = 0.0;
    double mass = 10.0;
    double density;
    double radius = 10.0;
    double r = 1.0;
    double g = 1.0;
    double b = 1.0;
    double vel_x = 0.0;
    double vel_y = 0.0;
    double acc_x = 0.0;
    double acc_y = 0.0;


    void tick(std::vector<Entity*>& objects);

    Entity(double x, double y, double mass, double radius, double r, double g, double b, double vel_x, double vel_y, double acc_x, double acc_y);
    Entity(double vel_x, double vel_y);
    Entity();
    ~Entity();
};

#endif