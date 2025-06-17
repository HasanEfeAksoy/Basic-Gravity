#include "../include/entity.h"

Entity::Entity(double x, double y, double mass, double radius, double r, double g, double b, double vel_x, double vel_y, double acc_x, double acc_y) {
    this->x = x;
    this->y = y;
    this->mass = mass;
    this->radius = radius;
    this->r = r;
    this->g = g;
    this->b = b;
    this->vel_x = vel_x;
    this->vel_y =  vel_y;
    this->acc_x =  acc_x;
    this->acc_y =  acc_y;
    this->density = this->mass / (4/3 * PI * this->radius * this->radius * this->radius);
}
Entity::Entity(double vel_x, double vel_y) {
    this->x = randDbl(-WIDTH/2, WIDTH/2);
    this->y = randDbl(-HEIGHT/2, HEIGHT/2);
    this->mass = randDbl(1, MAXMASS);
    this->radius = randDbl(1, MAXRADIUS);
    this->vel_x = vel_x;
    this->vel_y =  vel_y;
    this->density = this->mass / (4/3 * PI * this->radius * this->radius * this->radius);
    // this->r = randDbl(0.001, 1);
    // this->g = randDbl(0.001, 1);
    // this->b = randDbl(0.001, 1);
    this->r = 1;
    this->g = 1;
    this->b = 1 - this->mass / MAXMASS;
}
Entity::Entity() {
    this->x = randDbl(-WIDTH/2, WIDTH/2);
    this->y = randDbl(-HEIGHT/2, HEIGHT/2);
    this->mass = randDbl(0.0001, MAXMASS);
    this->radius = randDbl(1, MAXRADIUS);
    this->vel_x = randDbl(-0.1, 0.1);
    this->vel_y =  randDbl(-0.1, 0.1);
    this->density = this->mass / (4/3 * PI * this->radius * this->radius * this->radius);
    // this->r = randDbl(0.001, 1);
    // this->g = randDbl(0.001, 1);
    // this->b = randDbl(0.001, 1);
    this->r = 1;
    this->g = 1;
    this->b = 1 - this->mass / MAXMASS;
}
Entity::~Entity() {
}


void Entity::tick(std::vector<Entity*>& objects) {
    //gravity formula

    for (int i = 0; i < objects.size(); i++) {
        Entity* other = objects[i];

        if (other == this) continue;

        double dist_x = other->x - this->x;
        double dist_y = other->y - this->y;
        double dist = sqrt(dist_x * dist_x + dist_y * dist_y);

        if (dist < 0.001) continue;
        
        this->acc_x += (G * other->mass * dist_x) / (dist * dist * dist);
        this->acc_y += (G * other->mass * dist_y) / (dist * dist * dist);
    }
    
    
    
    this->density = this->mass / (4/3 * PI * this->radius * this->radius * this->radius);
    this->vel_x += this->acc_x;
    this->vel_y += this->acc_y;
    this->x += this->vel_x;
    this->y += this->vel_y;
    if (this != objects[0]) this->b = 1 - this->mass / MAXMASS;

    glColor3d(this->r, this->g, this->b);
    glBegin(GL_POLYGON);
    for (double i = 0; i < 2*PI; i+=2*PI/15) {
        glVertex2d(this->x + this->radius * cos(i), this->y + this->radius * sin(i));
    }
    glEnd();
}