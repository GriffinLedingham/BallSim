/*
 *
 * Open GL main file used in bouncing ball simulation.
 *
 * basicopenglview.cpp
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#include "basicopenglview.h"
#include "mainwindow.h"
#include <QTimer>
#include <OpenGL/glu.h>
#include <ctime>
#include <QtDebug>
#include <QSound>
#include <cmath>
#include "ball.h"
#include "surface.h"

int num_balls=1;
ball *sceneBalls[1] = {new ball(2,0.0f,9.0f,0.0f,.5f,.2f,.4f)};

bool nightOn;
extern bool mFor, mBack, mLeft, mRight, cUp, cDown, cLeft, cRight, cJump, cFall;
extern int nightmare;
extern int lockX;
extern int lockZ;
extern int sliderValue;
extern int sliderValue2;
extern int sliderValue3;
extern int disableAir;
float mass = 1;
float gravity = 0.03f;
float acceleration = mass*gravity;
float cameraZ = -10.0f;
float cameraX = 0.0f;
float cameraY = -3.0f;
float cameraRotHor = 0.0f;
float cameraRotVer = 10.0f;
//Variable used to enable and disable pong mode.
int pong = 0;

//Boolean used to enable and disable pong mode.
extern bool pongOn;

//Initialize the objects in the scene.
surface *myFloor = new surface(.5f,.5f,.5f,-40.0f,-2.0f,-40.0f,80.0f,0.0f,80.0f);
surface *wall1 = new surface(.5f,.5f,.5f,10.0f,-2.0f,-1.0f,0.0f,10.0f,14.0f);
surface *wall2 = new surface(.5f,.5f,.5f,10.0f,-2.0f,-14.0f,10.0f,10.0f,0.0f);
surface *wall3 = new surface(.5f,.5f,.5f,-13.0f,-2.0f,-1.0f,0.0f,10.0f,-12.0f);
surface *pongWall1 = new surface(.5f,.5f,.5f,-40.0f,-2.0f,-15.0f,80.0f,10.0f,0.0f);
surface *pongWall2 = new surface(.5f,.5f,.5f,-40.0f,-2.0f,15.0f,80.0f,10.0f,0.0f);

BasicOpenGLView::BasicOpenGLView(QWidget *parent) :
    QGLWidget(parent),
    projectionMatrix(),
    viewMatrix()
{
}

//initialize the QTimers used in the simulation.
void BasicOpenGLView::initializeGL()
{
    //Timer which updates the GL render.
    QTimer *timer = new QTimer();
    timer->start(17); //time in ms, here 1 ms
    connect(timer ,SIGNAL(timeout()),this,SLOT(updateGL()));

    //Timer which updates the scene objects.
    QTimer *animate = new QTimer();
    animate->start(1000); //time in ms, here 1 ms
    connect(timer ,SIGNAL(timeout()),this,SLOT(animateGL()));
}

void BasicOpenGLView::animateGL()
{
    //Set ball speed for pong mode.
    if(nightOn)
    {
        nightmare = 1;
    }
    else
    {
        nightmare = 0;
    }

    //Set pong mode on/off based on key input
    if(pongOn == true)
    {
        pong = 1;
        disableAir = 1;
    }
    else
    {
        pong = 0;
        disableAir = 0;
    }

    //If pong is enabled, set opponent Z coordinate equal to the ball
    //(The opponent is kind of cheating)
    if(pong == 1)
    {
        wall3->floorStartZ = sceneBalls[0]->ballZ+4;
        wall3->floorEndZ = wall3->floorStartZ+ wall3->zSize;
    }

    //Controls used to move camera, based on key input
    if(mFor == true)
    {
        if(pong == 0)
        {
            cameraX = cameraX - sin((cameraRotHor*3.141592)/180);
            cameraZ = cameraZ + cos((cameraRotHor*3.141592)/180);
        }
    }
    if(mBack == true)
    {
        if(pong == 0)
        {
            cameraX = cameraX + sin((cameraRotHor*3.141592)/180)*.5;
            cameraZ = cameraZ - cos((cameraRotHor*3.141592)/180)*.5;
        }

    }
    if(mLeft == true)
    {
        if(pong == 0)
        {
            cameraX = cameraX - sin(((cameraRotHor-90)*3.141592)/180);
            cameraZ = cameraZ + cos(((cameraRotHor-90)*3.141592)/180);
        }
        else if(pong == 1)
        {
            wall1->floorStartZ += 1;
            wall1->floorEndZ += 1;
        }
    }
    if(mRight == true)
    {
        if(pong==0)
        {
            cameraX = cameraX - sin(((cameraRotHor+90)*3.141592)/180);
            cameraZ = cameraZ + cos(((cameraRotHor+90)*3.141592)/180);
        }
        else if(pong == 1)
        {
            wall1->floorStartZ -= 1;
            wall1->floorEndZ -= 1;
        }
    }
    
    //Key input to spin the camera, only if pong mode is disabled
    if(cLeft == true)
    {
        if(pong==0)
        {
            cameraRotHor -= 3;

        }
    }
    if(cRight == true)
    {
        if(pong==0)
        {
            cameraRotHor += 3;

        }
    }
    
    //Pan camera up and down in the Y-Axis
    if(cJump == true)
    {
        cameraY -= 1;
    }
    if(cFall == true)
    {
        cameraY += 1;
    }

    //Calculate gravity, mass, and acceleration
    gravity = 0.03f*(float)sliderValue2/5;
    mass = 1+  (float)sliderValue/10;
    acceleration = gravity*mass;

    //Call ball movement function, and hit test functions in each object.
    //The ball and walls should be stored in arrays for easier detection/initialization, but was not required for this assignment.
    int i;
    for(i=0;i<num_balls;i++)
    {
        sceneBalls[i]->moveSim();
    }

    wall1->collide();
    wall3->collide();

    if(pong==0)
    {
        wall2->collide();
    }
    else
    {
        pongWall1->collide();
        pongWall2->collide();
    }
}

void BasicOpenGLView::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    //Set cameras based on free simulation mode, or pong mode
    if(pong==0)
    {
        viewMatrix.setToIdentity();
        viewMatrix.rotate(cameraRotHor,0,1,0);
        viewMatrix.rotate(cameraRotVer,1,0,0);
        viewMatrix.translate(cameraX,cameraY,cameraZ);
        viewMatrix.lookAt(QVector3D(0.0,3.0,-15.0),
                      QVector3D(0.0,4.0,0.0),
                      QVector3D(0.0,1.0,0.0));
        glLoadMatrixd(viewMatrix.data());
    }
    else
    {
        viewMatrix.setToIdentity();
        viewMatrix.rotate(60,1,0,0);
        viewMatrix.rotate(-90,0,1,0);
        viewMatrix.translate(-20.0f,-30.0f,0.0f);
        glLoadMatrixd(viewMatrix.data());
    }

    glPushMatrix();

    //Initialize lighting
    GLfloat light_pos[] = {1.0, 2.0, 3.0, 1.0};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity( );
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);

    glPopMatrix();

    //Spawn objects based whether pong mode is enabled or disabled
    int i;
    for(i=0;i<num_balls;i++)
    {
        sceneBalls[i]->spawn();
    }

    myFloor->spawn();
    wall1->spawn();
    wall3->spawn();

    if(pong==0)
    {
        wall2->spawn();
    }
    else
    {
        pongWall1->spawn();
        pongWall2->spawn();
    }
}

void BasicOpenGLView::resizeGL(int w, int h)
{
    //Resize GL window
    glViewport(0,0,w,h);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(60.0f,
                                 (float)w/(float)h,
                                 0.1,
                                 50.0);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(projectionMatrix.data());

    glMatrixMode(GL_MODELVIEW);
}
