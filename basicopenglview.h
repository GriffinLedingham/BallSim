/*
 *
 * Open GL main header file used in bouncing ball simulation.
 *
 * basicopenglview.h
 * Griffin Ledingham
 * V00712188
 * Assignment 1
 * CSC 473
 *
 */

#ifndef BASICOPENGLVIEW_H
#define BASICOPENGLVIEW_H

#include <QGLWidget>
#include <QMatrix4x4>

class BasicOpenGLView : public QGLWidget
{
    Q_OBJECT
public:
    explicit BasicOpenGLView(QWidget *parent = 0);
private slots:
    void animateGL();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
private:
    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;
};

#endif // BASICOPENGLVIEW_H
