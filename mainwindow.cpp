/*
 *
 * Main UI Window file used in bouncing ball simulation.
 *
 * mainwindow.cpp
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ball.h"
#include <ctime>

extern int num_balls;
extern ball* sceneBalls[1];

bool pongOn;
bool mFor, mBack, mLeft, mRight, cUp, cDown, cLeft, cRight, cJump, cFall;
extern bool nightOn;
extern int pong;
extern float cameraZ;
extern float cameraX;
extern float cameraY;
extern float mass;
extern float gravity;
extern float cameraRotHor;
extern float cameraRotVer;
int disableAir=0;
int sliderValue;
int sliderValue2=5;
int sliderValue3;
int lockX=0;
int lockZ=0;
int nightmare=0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Slider QT slots used for setting values based on UI sliders
void MainWindow::on_verticalSlider_valueChanged(int value)
{
    sliderValue = value;
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{
    sliderValue2 = value;
}

//Push button QT slot
void MainWindow::on_pushButton_clicked()
{
    int i;
    for(i=0;i<num_balls;i++)
    {
        float denominator;
        if(pong == 1 && nightmare == 1)
        {
            denominator = 0.5f;
        }
        else if(pong == 1 && nightmare ==0)
        {
            denominator = 2.0f;
        }
        else
        {
            denominator = 3.0f;
        }
        sceneBalls[i]->ballRed = ((float)rand()/(float)RAND_MAX)/2;
        sceneBalls[i]->ballGreen = ((float)rand()/(float)RAND_MAX)/2;
        sceneBalls[i]->ballBlue = ((float)rand()/(float)RAND_MAX)/2;
        int a=rand()%2;
        if(a)
        {
            sceneBalls[i]->xvelocity = ((float)rand()/(float)RAND_MAX)/denominator;
        }
        else
        {
            sceneBalls[i]->xvelocity = (-(float)rand()/(float)RAND_MAX)/denominator;
        }
        a=rand()%2;
        if(a)
        {
            sceneBalls[i]->zvelocity = ((float)rand()/(float)RAND_MAX)/denominator;
        }
        else
        {
            sceneBalls[i]->zvelocity = (-(float)rand()/(float)RAND_MAX)/denominator;
        }

        sceneBalls[i]->ballZ = 0.0f;
        sceneBalls[i]->ballX = 0.0f;
        sceneBalls[i]->ballY = 9.0f;
        mass = 1;
        gravity = 0.03f;
        sceneBalls[i]->velocity = 0.0f;
    }
}

//Slider QT slots used for setting values based on UI sliders
void MainWindow::on_verticalSlider_3_valueChanged(int value)
{
    sliderValue3 = value;
}

//Checkbox QT slots used for setting values based on UI sliders
void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    lockX = arg1;
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    lockZ = arg1;
}

//Keyboard event used to take key input and modify the simulation/scene
//Uses a polling system in the GL main loop to allow for smooth movement
//Key press enables a boolean, key releases disables the boolean, and the main loop reads these booleans
void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if(event->text() =="w")
    {
        mFor = true;
    }

    if(event->text() == "s")
    {
        mBack = true;
    }

    if(event->text() =="a")
    {
        mLeft = true;
    }

    if(event->text() == "d")
    {
        mRight = true;
    }

    if(event->text() == "-") //down
    {
        cFall = true;
    }

    if(event->text() == "=") //up
    {
        cJump = true;
    }

    if(event->key() == Qt::Key_Left) //rot left
    {
        cLeft = true;
    }

    if(event->key() == Qt::Key_Right) //rot right
    {
        cRight = true;
    }

    if(event->key() == Qt::Key_Up) //rot up
    {
        cUp = true;
    }

    if(event->key() == Qt::Key_Down) //rot down
    {
        cDown = true;
    }

    if(event->text() == "r")
    {
        cameraRotHor = 0.0f;
        cameraRotVer = 10.0f;
        cameraX = 0.0f;
        cameraY = -3.0f;
        cameraZ = -10.0f;
    }

    if(event->text() == " ")
    {
        int i;
        for(i=0;i<num_balls;i++)
        {
            float denominator;
            if(pong == 1 && nightmare == 1)
            {
                denominator = 0.5f;
            }
            else if(pong == 1 && nightmare ==0)
            {
                denominator = 2.0f;
            }
            else
            {
                denominator = 3.0f;
            }
            sceneBalls[i]->ballRed = ((float)rand()/(float)RAND_MAX)/2;
            sceneBalls[i]->ballGreen = ((float)rand()/(float)RAND_MAX)/2;
            sceneBalls[i]->ballBlue = ((float)rand()/(float)RAND_MAX)/2;
            int a=rand()%2;
            if(a)
            {
                sceneBalls[i]->xvelocity = ((float)rand()/(float)RAND_MAX)/denominator;
            }
            else
            {
                sceneBalls[i]->xvelocity = (-(float)rand()/(float)RAND_MAX)/denominator;
            }
            a=rand()%2;
            if(a)
            {
                sceneBalls[i]->zvelocity = ((float)rand()/(float)RAND_MAX)/denominator;
            }
            else
            {
                sceneBalls[i]->zvelocity = (-(float)rand()/(float)RAND_MAX)/denominator;
            }

            sceneBalls[i]->ballZ = 0.0f;
            sceneBalls[i]->ballX = 0.0f;
            sceneBalls[i]->ballY = 9.0f;
            mass = 1;
            gravity = 0.03f;
            sceneBalls[i]->velocity = 0.0f;
        }
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event)
{
    if(event->text() == "w")
    {
        mFor = false;
    }

    if(event->text() == "s")
    {
        mBack = false;
    }

    if(event->text() == "a")
    {
        mLeft = false;
    }

    if(event->text() == "d")
    {
        mRight = false;
    }

    if(event->text() == "-") //down
    {
        cFall = false;
    }

    if(event->text() == "=") //up
    {
        cJump = false;
    }

    if(event->key() == Qt::Key_Left) //rot left
    {
        cLeft = false;
    }

    if(event->key() == Qt::Key_Right) //rot right
    {
        cRight = false;
    }

    if(event->key() == Qt::Key_Up) //rot up
    {
        cUp = false;
    }

    if(event->key() == Qt::Key_Down) //rot down
    {
        cDown = false;
    }
}

//Push button QT slot
void MainWindow::on_pushButton_2_clicked()
{
    cameraRotHor = 0.0f;
    cameraRotVer = 10.0f;
    cameraZ = -10.0f;
    cameraX = 0.0f;
    cameraY = -3.0f;
}

//Checkbox QT slots used for setting values based on UI sliders
void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    disableAir=arg1;
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1)
    {
        pongOn = true;
    }
    else
    {
        pongOn = false;
    }
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1)
    {
        nightOn = true;
    }
    else
    {
        nightOn = false;
    }
}
