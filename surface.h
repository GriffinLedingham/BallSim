/*
 *
 * Surface class header file used in bouncing ball simulation.
 *
 * surface.h
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#ifndef SURFACE_H
#define SURFACE_H

#include <OpenGL/glu.h>
#include <ctime>
#include <QtDebug>
#include <cmath>

class surface{

public:
    float floorRed, floorGreen, floorBlue;
    float floorStartX,floorEndX,floorStartY,floorEndY,floorStartZ,floorEndZ,zSize,ySize,xSize;
    surface(float,float,float,float,float,float,float,float,float);
    void spawn();
    void collide();
};

#endif // SURFACE_H
