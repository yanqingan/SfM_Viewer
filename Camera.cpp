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

#include <qgl.h>
#include <QString>
#include <math.h>
#include <GL/glu.h>
#include "Camera.h"

#define THUMB_RATIO 1000.0
#define PI 3.14159
Camera::Camera()
{
    m_showMode = 0;
    m_bFlag = true;
    m_bLoad = false;
    m_nWidth = 0.0;
    m_nHeight = 0.0;
    m_nDepth = 0.0;
}

Camera::~Camera()
{

}

void Camera::ChangeMode()
{
    m_showMode++;
    m_showMode %= 3;
}

void Camera::ShowFramework()
{
    if(!m_bFlag)
       return;
    float pos[3] = {0.0f, 0.0f, 0.0f};
    float dir[3] = {0.0f, 0.0f, 0.0f};
    float tmp[3] = {0.0f, 0.0f, -1.0f};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            pos[i] += -R[i + j * 3] * t[j];
            dir[i] += R[i + j * 3] * tmp[j];
        }
    }
    glPushMatrix();
    glTranslatef(pos[0], pos[1], pos[2]);
    float zRay[3] = {0.0f, 0.0f, -1.0f};
    float normal[3] = {0.0f};
    normal[0] = dir[1];
    normal[1] = -1.0f * dir[0];
    normal[2] = 0.0f;
    float aa = 0.05f;
    float angle = 180.0f / PI * acos(-1.0f * dir[2] / sqrt(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]));
    glRotatef(angle, normal[0], normal[1], normal[2]);
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex3f(-aa, aa, -aa);
    glVertex3f(aa, aa, -aa);
    glVertex3f(aa, aa, -aa);
    glVertex3f(aa, -aa, -aa);
    glVertex3f(aa, -aa, -aa);
    glVertex3f(-aa, -aa, -aa);
    glVertex3f(-aa, -aa, -aa);
    glVertex3f(-aa, aa, -aa);
    glVertex3f(-aa, aa, -aa);
    glVertex3f(aa, -aa, -aa);
    glVertex3f(aa, aa, -aa);
    glVertex3f(-aa, -aa, -aa);
    glEnd();
    glColor3f(1.0f, 0.0f, 0.0f);
    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex3f(-aa, aa, -aa);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(aa, aa, -aa);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(aa, -aa, -aa);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-aa, -aa, -aa);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
}

int Camera::InitTexture(int texture)
{
    if (m_showMode == 1)
        return 0;
    QImage m_image;
    if(!m_image.load(QString("../yan-SightExplorer12-C-v1/textures/%1.jpg").arg(m_id)))
    {
        qWarning("Could not read image file!");
        return 0;
    }
    m_bLoad = true;
    m_texture = texture;
    m_nWidth = (float)m_image.width() / THUMB_RATIO;
    m_nHeight = (float)m_image.height() / THUMB_RATIO;
    m_nDepth = f / THUMB_RATIO;
    QImage buf;
    buf = QGLWidget::convertToGLFormat(m_image);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, buf.width(), buf.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, buf.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);    // parameter for m_texture id texture
    glTexParameteri(GL_TEXTURE_2D ,GL_TEXTURE_MAG_FILTER, GL_LINEAR);    // very important, if no, there is not texture displayed
    return 1;
}

int Camera::ShowThumbnail()
{
    if((!m_bLoad) || (!m_bFlag))
    {
        return 0;
    }
    glPushMatrix();
    /* if change the order */
    float m[16] = {R[0], R[3], R[6], 0.0, R[1], R[4], R[7], 0.0, R[2], R[5], R[8], 0.0, t[0], t[1], t[2], 1.0};
    /* if not change the order */
    //float m[16] = {R[0], R[1], R[2], 0.0, R[3], R[4], R[5], 0.0, R[6], R[7], R[8], 0.0, t[0], t[1], t[2], 1.0};
    float x, y, z;
    x = m_nWidth * 0.5;
    y = m_nHeight * 0.5;
    z = m_nDepth;
    glMultMatrixf(m);
    glEnable(GL_TEXTURE_2D);    // need
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);    // very important attribute
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-x, -y, -z);
    glTexCoord2f(1.0, 0.0); glVertex3f(x, -y, -z);
    glTexCoord2f(1.0, 1.0); glVertex3f(x, y, -z);
    glTexCoord2f(0.0, 1.0); glVertex3f(-x, y, -z);
    glEnd();
    glFlush();    // needless
    glDisable(GL_TEXTURE_2D);    // need
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-x, -y, -z);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x, -y, -z);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(x, y, -z);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(-x, y, -z);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glEnd();
    glPopMatrix();
    return 1;
}

void Camera::Draw()
{
    if(m_showMode == 1)
        ShowFramework();
    else if(m_showMode == 2)
        ShowThumbnail();
}
