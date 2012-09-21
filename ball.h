/*
 *
 * Ball class header file used in bouncing ball simulation.
 *
 * ball.h
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#ifndef BALL_H
#define BALL_H

#include <OpenGL/glu.h>
#include <ctime>
#include <QtDebug>
#include <cmath>

class ball{

public:
    float ballRed, ballGreen, ballBlue;
    float ballX, ballY, ballZ;
    int ballRadius;
    float velocity,xvelocity,zvelocity;
    ball(int,float,float,float,float,float,float);
    void spawn();
    void moveSim();
};

#endif // BALL_H
