/*
 *
 * Surface class file used in bouncing ball simulation.
 *
 * surface.cpp
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#include "surface.h"
#include "ball.h"

extern ball *myBall;
extern int pong;

//Surface class constructor
surface::surface(float red, float green, float blue, float startX,float startY,float startZ,float sizeX, float sizeY, float sizeZ)
{
    floorRed = red;
    floorGreen = green;
    floorBlue = blue;

    floorStartX = startX;
    floorStartY = startY;
    floorStartZ = startZ;

    floorEndX = startX + sizeX;
    floorEndY = startY + sizeY;
    floorEndZ = startZ + sizeZ;

    zSize = sizeZ;
    xSize = sizeX;
    ySize = sizeY;
}

//Function to populate the scene with surfaces
void surface::spawn()
{
    float mat_ambient_color[] = {floorRed, floorGreen, floorBlue, 1.0f};
    float high_shininess = 100.0f;
    float mat_specular[] = {1.0f, 1.0f,1.0f, 1.0f};
    float no_mat[] = {floorRed, floorGreen, floorBlue, 1.0f};
    float mat_diffuse[] = {floorRed, floorGreen, floorBlue, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

    glBegin(GL_TRIANGLES);
    glVertex3f(floorStartX,floorStartY,floorEndZ);
    glVertex3f(floorEndX,floorEndY,floorEndZ);
    glVertex3f(floorStartX,floorEndY,floorStartZ);

    glVertex3f(floorEndX,floorStartY,floorEndZ);
    glVertex3f(floorStartX,floorStartY,floorStartZ);
    glVertex3f(floorEndX,floorEndY,floorStartZ);
    glEnd();
}

//Collision detection for the surfaces and the ball
void surface::collide()
{
    float hitTestYStart, hitTestYEnd,hitTestXStart, hitTestXEnd,hitTestZStart, hitTestZEnd;

    if(floorStartY<0)
    {
        hitTestYStart = floorStartY + 2.0f;
    }
    else
    {
        hitTestYStart = floorStartY + 2.0f;
    }
    if(floorEndY<0)
    {
        hitTestYEnd = floorEndY + 2.0f;
    }
    else
    {
        hitTestYEnd = floorEndY + 2.0f;
    }

    if(floorStartX>floorEndX)
    {
        hitTestXStart = floorStartX + 2.0f;
        hitTestXEnd = floorEndX - 2.0f;
    }
    else
    {
        hitTestXStart = floorStartX - 2.0f;
        hitTestXEnd = floorEndX + 2.0f;
    }

    if(floorStartZ>floorEndZ)
    {
        hitTestZStart = floorStartZ + 2.0f;
        hitTestZEnd = floorEndZ - 2.0f;
    }
    else
    {
        hitTestZStart = floorStartZ - 2.0f;
        hitTestZEnd = floorEndZ + 2.0f;
    }

    if(pong == 1 && hitTestXStart <0 && floorStartX == floorEndX)
    {
        if(myBall->ballY>=-0.03 && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ>(hitTestZEnd) && myBall->ballZ<(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXEnd;

        }
    }
    else if(pong == 1 && hitTestXStart>0 && floorStartX == floorEndX)
    {
        if(myBall->ballY>=-0.03 && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXStart;

        }
    }
    else if(floorStartX == floorEndX && floorStartZ>0 && floorEndZ>0) //both Z points bove 0
    {
        if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXStart;

        }
    }
    else if(floorStartX == floorEndX && floorStartZ<0 && floorEndZ<0) //both Z points below 0
    {
        if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ>(hitTestZEnd) && myBall->ballZ<(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXEnd;

        }
    }
    else if(floorStartX == floorEndX && floorStartZ>0 && floorEndZ<0) //start above 0 end below 0
    {
        if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ>(hitTestZEnd) && myBall->ballZ<(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXEnd;

        }
    }
    else if(floorStartX == floorEndX) //start below 0 end above 0
    {
        if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
        {
            myBall->xvelocity = -myBall->xvelocity;
            myBall->ballX = hitTestXStart;

        }
    }
    else if(floorStartZ == floorEndZ && floorStartZ >0)
    {
        if(pong==1)
        {
            if(myBall->ballY>=-0.03f && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
            {
                myBall->zvelocity = -myBall->zvelocity;
                myBall->ballZ = hitTestZStart;
            }
        }
        else if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
        {
            myBall->zvelocity = -myBall->zvelocity;
            myBall->ballZ = hitTestZStart;
        }
    }
    else if(floorStartZ == floorEndZ)
    {
        if(pong==1)
        {
            if(myBall->ballY>=-0.03f && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
            {
                myBall->zvelocity = -myBall->zvelocity;
                myBall->ballZ = hitTestZEnd;
            }
        }
        else if(myBall->ballY>=(hitTestYStart) && myBall->ballY<(hitTestYEnd) && myBall->ballX>(hitTestXStart) && myBall->ballX<(hitTestXEnd) && myBall->ballZ<(hitTestZEnd) && myBall->ballZ>(hitTestZStart))
        {
            myBall->zvelocity = -myBall->zvelocity;
            myBall->ballZ = hitTestZEnd;
        }
    }

}
