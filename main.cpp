/*
 *
 * Program main file used in bouncing ball simulation.
 *
 * main.cpp
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
