/*
 *
 * Ball class file used in bouncing ball simulation.
 *
 * ball.cpp
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#include "ball.h"

extern float acceleration;
extern int lockX,lockZ,disableAir,sliderValue3;

//Constructor for the ball class.
//Set ball's color, radius and initial coordinates.
ball::ball(int radius, float x, float y, float z, float red, float green, float blue)
{
    velocity = 0.0f;
    ballRed = red;
    ballGreen = green;
    ballBlue = blue;
    ballX = x;
    ballY = y;
    ballZ = z;
    ballRadius = radius;
}

//Function which moves the ball.
void ball::moveSim()
{
    if(ballY<0.0f)
        {
            if(velocity>-0.028f && velocity<=0.06)
            {
                //Over-travel correction
                velocity = 0.0f;
            }
            if(disableAir==0)
            {
                //Air Resistance/Energy Loss
                velocity = -velocity/1.15;
            }
            else
            {
                //No Resistance/Energy Loss
                velocity = -velocity;
            }
            ballY=0.0f;
            //Friction
            xvelocity -= sliderValue3/12;
            zvelocity -= sliderValue3/12;
        }

        velocity+=acceleration;
        ballY-=velocity;

        //Lock X coordinates
        if(lockX==0)
        {
            ballX -=xvelocity;
        }
        
        //Lock Z coordinates
        if(lockZ==0)
        {
            ballZ -=zvelocity;
        }
}

//Load the ball object into the scene
void ball::spawn()
{
    //color
    float mat_ambient_color[] = {ballRed, ballGreen, ballBlue, 1.0f};
    float high_shininess = 100.0f;
    float mat_specular[] = {1.0f, 1.0f,1.0f, 1.0f};
    float no_mat[] = {ballRed, ballGreen, ballBlue, 1.0f};
    float mat_diffuse[] = {ballRed, ballGreen, ballBlue, 1.0f};

    //set material
    glPushMatrix();
    glTranslatef(ballX, ballY, ballZ);
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    //create the glu sphere
    GLUquadricObj *quadric;
    quadric = gluNewQuadric();
    gluQuadricDrawStyle(quadric, GLU_FILL );
    gluSphere(quadric,ballRadius,1000,1000);
    gluDeleteQuadric(quadric);
    glPopMatrix();
}
