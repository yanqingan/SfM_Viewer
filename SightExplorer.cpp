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

#include <GL/glu.h>
#include <math.h>
#include "SightExplorer.h"

SightExplorer::SightExplorer()
{
    m_nPlyFile = 0;
    m_nOutFile = 0;
    m_pPlyFiles = NULL;
    m_pOutFiles = NULL;
    m_nX = 0.0f;
    m_nY = 0.0f;
    m_nZ = 0.0f;
    m_lastR.SetIndentify();
    m_newR.SetIndentify();
    m_T.SetIndentify();
}

SightExplorer::~SightExplorer()
{
    if(m_nPlyFile)
    {
        if(m_nPlyFile == 1)
            delete m_pPlyFiles;
        else
            delete[] m_pPlyFiles;
        m_pPlyFiles = NULL;
    }
    if(m_nOutFile)
    {
        if(m_nOutFile == 1)
            delete m_pOutFiles;
        else
            delete[] m_pOutFiles;
        m_pOutFiles = NULL;
    }
}

void SightExplorer::Start2Sphere()
{
    float x = m_startPos.x();
    float y = m_startPos.y();
    x = x * (1.0 / ((m_nWidth - 1.0) * 0.5)) - 1.0;
    y = 1.0 - (y * (1.0 / ((m_nHeight - 1.0) * 0.5)));
    float d2 = x * x + y * y;
    if(d2 > 1.0)
    {
        float norm = 1.0 / sqrtf(d2);
        m_startSphere.x = x * norm;
        m_startSphere.y = y * norm;
        m_startSphere.z = 0.0;
    }
    else
    {
        m_startSphere.x = x;
        m_startSphere.y = y;
        m_startSphere.z = sqrtf(1 - d2);
    }
}

void SightExplorer::LeftMousePress()
{

}

void SightExplorer::RightMousePress()
{
    Start2Sphere();
}

void SightExplorer::WheelRoll(float degrees)
{
    float steps = degrees / 15;
    m_nZ += steps;
}

void SightExplorer::DrawPlyFiles()
{
    if(m_nPlyFile)
    {
        for(int i = 0; i < m_nPlyFile; i++)
        {
            m_pPlyFiles[i].Draw();
        }
    }
}

void SightExplorer::DrawOutFiles()
{
    if(m_nOutFile)
    {
        for(int i = 0; i < m_nOutFile; i++)
        {
            m_pOutFiles[i].Draw();
        }
    }
}

void SightExplorer::New2Sphere()
{
    float x = m_newPos.x();
    float y = m_newPos.y();
    x = x * (1.0 / ((m_nWidth - 1.0) * 0.5)) - 1.0;
    y = 1.0 - (y * (1.0 / ((m_nHeight - 1.0) * 0.5)));
    float d2 = x * x + y * y;
    if(d2 > 1.0)
    {
        float norm = 1.0 / sqrtf(d2);
        m_newSphere.x = x * norm;
        m_newSphere.y = y * norm;
        m_newSphere.z = 0.0;
    }
    else
    {
        m_newSphere.x = x;
        m_newSphere.y = y;
        m_newSphere.z = sqrtf(1 - d2);
    }
}

void SightExplorer::LeftMouseMove()
{
    m_nX += (m_newPos.x() - m_startPos.x()) / 2;
    m_nY -= (m_newPos.y() - m_startPos.y()) / 2;
}

void SightExplorer::RightMouseMove()
{
    New2Sphere();
    Vector3f v3;
    v3 = m_startSphere.CrossProduct(m_newSphere);
    float len = sqrtf(v3.Norm_2());
    if(len > Epsilon)
    {
        m_moveQuater.x = v3.x;
        m_moveQuater.y = v3.y;
        m_moveQuater.z = v3.z;
        m_moveQuater.w = m_startSphere.DotProduct(m_newSphere);
    }
    else
        m_moveQuater.x = m_moveQuater.y = m_moveQuater.z = m_moveQuater.w = 0.0;
}

void SightExplorer::Quater2Rot()
{
    float n, s;
    float xs, ys, zs;
    float wx, wy, wz;
    float xx, xy, xz;
    float yy, yz, zz;
    n = m_moveQuater.Norm_2();
    s = (n > 0.0) ? (2.0 / n) : 0.0;

    xs = m_moveQuater.x * s;  ys = m_moveQuater.y * s;  zs = m_moveQuater.z * s;
    wx = m_moveQuater.w * xs; wy = m_moveQuater.w * ys; wz = m_moveQuater.w * zs;
    xx = m_moveQuater.x * xs; xy = m_moveQuater.x * ys; xz = m_moveQuater.x * zs;
    yy = m_moveQuater.y * ys; yz = m_moveQuater.y * zs; zz = m_moveQuater.z * zs;

    m_newR.m_mat[0] = 1.0f - (yy + zz); m_newR.m_mat[3] =         xy - wz;  m_newR.m_mat[6] =         xz + wy;
    m_newR.m_mat[1] =         xy + wz;  m_newR.m_mat[4] = 1.0f - (xx + zz); m_newR.m_mat[7] =         yz - wx;
    m_newR.m_mat[2] =         xz - wy;  m_newR.m_mat[5] =         yz + wx;  m_newR.m_mat[8] = 1.0f - (xx + yy);
}

void SightExplorer::LoadPlyFiles(QStringList filenames, int num)
{
    ClearSight();
    m_pPlyFiles = new PlyFile[num];
    m_nPlyFile = num;
    for(int i = 0; i < num; i++)
    {
        QByteArray ba = filenames[i].toLatin1();    // convert QString to char* or const char*
        const char *c_str = ba.data();
        m_pPlyFiles[i].Load(c_str);
    }
    updateGL();
}

void SightExplorer::LoadOutFiles(QStringList filenames, int num)
{
    ClearSight();
    m_pOutFiles = new OutFile[num];
    m_nOutFile = num;
    for(int i = 0; i < num; i++)
    {
        QByteArray ba = filenames[i].toLatin1();    // convert QString to char* or const char*
        const char *c_str = ba.data();
        m_pOutFiles[i].Load(c_str);
    }
    updateGL();
}

void SightExplorer::ClearSight()
{
    if(m_nPlyFile)
    {
        if(m_nPlyFile == 1)
            delete m_pPlyFiles;
        else
            delete[] m_pPlyFiles;
        m_pPlyFiles = NULL;
        m_nPlyFile = 0;
    }
    if(m_nOutFile)
    {
        if(m_nOutFile == 1)
            delete m_pOutFiles;
        else
            delete[] m_pOutFiles;
        m_pOutFiles = NULL;
        m_nOutFile = 0;
    }
    m_lastR.SetIndentify();
    m_newR.SetIndentify();
    m_T.SetIndentify();
    m_nX = 0.0f;
    m_nY = 0.0f;
    m_nZ = 0.0f;
    updateGL();
}

void SightExplorer::initializeGL()
{
    //glShadeModel(GL_SMOOTH);
    glShadeModel(GL_FLAT);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void SightExplorer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    /* translate the scene */
    glTranslatef(m_nX, m_nY, m_nZ);
    /* rotate the scene */
    glMultMatrixf(m_T.m_mat);
    DrawPlyFiles();
    DrawOutFiles();
}

void SightExplorer::resizeGL(int width, int height)
{
    if(height == 0)
    {
        height = 1;
    }
    m_nWidth = width;
    m_nHeight = height;
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, -10.0, 0.0, 1.0, 0.0);
    //glFrustum(-1.0, 1.0, -1.0, 1.0, 0.1, 20.0);
    //glOrtho(-10.0, 10.0, -10.0, 10.0, 0.1, 100.0);
    gluPerspective(60.0, 1.0, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}


void SightExplorer::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        m_startPos = event->pos();
        LeftMousePress();
    }
    else if(event->buttons() & Qt::RightButton)
    {
        m_lastR = m_newR;
        m_startPos = event->pos();
        RightMousePress();
    }
}

void SightExplorer::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        m_newPos = event->pos();
        LeftMouseMove();
        m_startPos = m_newPos;
    }
    else if(event->buttons() & Qt::RightButton)
    {
        m_newPos = event->pos();
        RightMouseMove();
        Quater2Rot();
        m_newR.RightProduct_cm(m_lastR);
        m_T = m_newR;
    }
    updateGL();
}

void SightExplorer::wheelEvent(QWheelEvent *event)
{
    float degrees = (float)event->delta() / 8;   // delta() +-120
    WheelRoll(degrees);
    updateGL();
}

void SightExplorer::keyPressEvent(QKeyEvent *e)
{
    switch(e->key())
    {
    case Qt::Key_F2:
        for(int i = 0; i < m_nOutFile; i++)
            m_pOutFiles[i].ChangeCameraMode();
        updateGL();
        break;
    }
}
