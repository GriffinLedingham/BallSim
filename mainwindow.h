/*
 *
 * Main UI Window header file used in bouncing ball simulation.
 *
 * mainwindow.h
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_verticalSlider_valueChanged(int value);
    void on_verticalSlider_2_valueChanged(int value);


    void on_pushButton_clicked();

    void on_verticalSlider_3_valueChanged(int value);

    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);


    void on_pushButton_2_clicked();

    void on_checkBox_3_stateChanged(int arg1);

    void on_checkBox_4_stateChanged(int arg1);

    void on_checkBox_5_stateChanged(int arg1);

protected:
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
