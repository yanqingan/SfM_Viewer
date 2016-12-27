/*********************************************************************************
  *Copyright(C) 2013-2016 Qingan Yan (yanqinganssg (at) gmail.com or yanqingan (at) whu.edu.cn)
  *Author: Qingan Yan
  *Version: v15.2
  *Date: Sep-10-2015

  *Description: This program is used to display point clouds from .out and .ply file format,
   which is the output of Bundler.

  *Notice: This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation.

  *For more information, please view my homepage at https://yanqingan.github.io
**********************************************************************************/

#ifndef SIGHTEXPLORER_H
#define SIGHTEXPLORER_H

#include <qgl.h>
#include <QKeyEvent>
#include <QMouseEvent>
#include <GL/glu.h>
#include "Matrixnt.h"
#include "Vectornt.h"
#include "Quaternion.h"
#include "PlyFile.h"
#include "OutFile.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_WIDTH_MIN 320
#define WINDOW_HEIGHT_MIN 240
#define Epsilon 1.0e-5

class SightExplorer : public QGLWidget
{
public:
    SightExplorer();
    ~SightExplorer();
    void LoadPlyFiles(QStringList filenames, int num);
    void LoadOutFiles(QStringList filenames, int num);
    void ClearSight();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent * event);
    void keyPressEvent(QKeyEvent *e);

private slots:
    void LeftMousePress();
    void LeftMouseMove();
    void RightMousePress();
    void RightMouseMove();
    void WheelRoll(float degrees);

private:
    void Start2Sphere();
    void New2Sphere();
    void Quater2Rot();
    void DrawPlyFiles();
    void DrawOutFiles();

    int m_nWidth;
    int m_nHeight;
    int m_nPlyFile;
    int m_nOutFile;
    float m_nX;
    float m_nY;
    float m_nZ;
    Matrix3f m_lastR;
    Matrix3f m_newR;
    Matrix4f m_T;
    QPoint m_startPos;
    QPoint m_newPos;
    Vector3f m_startSphere;
    Vector3f m_newSphere;
    Quaternion m_moveQuater;
    PlyFile *m_pPlyFiles;
    OutFile *m_pOutFiles;
};

#endif // SIGHTEXPLORER_H
