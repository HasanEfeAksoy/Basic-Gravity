#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#include "../resources/glfw/include/GLFW/glfw3.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

#define WIDTH 1800
#define HEIGHT 900
#define TITLE "Gravity Simultaion [Hold Left Click To Make A Black Hole] | Hasan Efe Aksoy"
#define PI 3.14159265
#define G 0.000001
#define COUNT 1000
#define MAXMASS 2000
#define MAXRADIUS 10

#define MOUSEENTITYMASS 10000000
#define MOUSEENTITYRADIUS 20


inline double randDbl(double min, double max) {
    double scale = rand() / (double) RAND_MAX;
    return min + scale * (max - min);
}

inline double calculateNewRadius(double r1, double r2) {
    double v1 = (4.0/3.0) * PI * pow(r1, 3);
    double v2 = (4.0/3.0) * PI * pow(r2, 3);
    double v_new = v1 + v2;

    return cbrt((3.0 / (4.0 * PI)) * v_new);
}


#endif