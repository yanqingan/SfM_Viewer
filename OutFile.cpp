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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <qgl.h>
#include "OutFile.h"

OutFile::OutFile()
{
    m_pVertices = NULL;
    m_pColors = NULL;
    m_pCameras = NULL;
    m_pTextures = NULL;
    m_nVertex = 0;
    m_nCamera = 0;
    m_bTex = true;
}

OutFile::~OutFile()
{
    if(m_pVertices)
    {
        free(m_pVertices);
        m_pVertices = NULL;
    }
    if(m_pColors)
    {
        free(m_pColors);
        m_pColors = NULL;
    }
    if(m_nCamera == 1)
    {
        delete m_pCameras;
        m_pCameras = NULL;
    }
    else if(m_nCamera > 1)
    {
        delete[] m_pCameras;
        m_pCameras = NULL;
    }
    if(m_pTextures)
    {
        free(m_pTextures);
        m_pTextures = NULL;
    }
}

int OutFile::Load(const char* filename)
{
    /* whether is a out file */
    char* pCh = strstr(filename, ".out");    // return the position
    if (pCh != NULL)
    {
        FILE* file = fopen(filename, "r");
        fseek(file, 0, SEEK_SET);    // this is SEEK_SET
        if (file)
        {
            int i = 0;
            int r, g, b;
            char buf[1000];
            fgets(buf, 300, file);   // read (300 - 1) bytes or a line
            /* read header */
            while(strncmp("# Bundle file", buf, strlen("# Bundle file")) != 0)    // string comparsion, if equal return 0
            {
                fgets(buf, 300, file);    // read again
            }
            fscanf(file, "%d %d", &m_nCamera, &m_nVertex);    // read a format data from a string
            try
            {
                m_pVertices = (float*)malloc(3 * m_nVertex * sizeof(float));
                m_pColors = (float*)malloc(3 * m_nVertex * sizeof(float));
                m_pCameras = new Camera[m_nCamera];
            }
            catch(char*)
            {
                printf("Exception in malloc vertex buffer of OutFile::load()!\n");
                return -1;
            }
            if(m_pVertices == NULL)
                return -1;
            /* read cameras */
            for(int iter = 0; iter < m_nCamera; iter++)
            {
                fscanf(file, "%f %f %f", &m_pCameras[iter].f, &m_pCameras[iter].k[0], &m_pCameras[iter].k[1]);
                fscanf(file, "%f %f %f", &m_pCameras[iter].R[0], &m_pCameras[iter].R[1], &m_pCameras[iter].R[2]);
                fscanf(file, "%f %f %f", &m_pCameras[iter].R[3], &m_pCameras[iter].R[4], &m_pCameras[iter].R[5]);
                fscanf(file, "%f %f %f", &m_pCameras[iter].R[6], &m_pCameras[iter].R[7], &m_pCameras[iter].R[8]);
                fscanf(file, "%f %f %f", &m_pCameras[iter].t[0], &m_pCameras[iter].t[1], &m_pCameras[iter].t[2]);
                if(!m_pCameras[iter].f)
                    m_pCameras[iter].SetFlag(false);
                m_pCameras[iter].SetId(iter);
            }
            /* read vertices and colors */
            i = 0;
            for(int iter = 0; iter < m_nVertex; iter++)
            {
                fscanf(file, "%f %f %f", &m_pVertices[i], &m_pVertices[i + 1], &m_pVertices[i + 2]);    // vertices
                fscanf(file, "%d %d %d", &r, &g, &b);    // colors
                m_pColors[i] = (float)r / 255.0f;
                m_pColors[i + 1] = (float)g / 255.0f;
                m_pColors[i + 2] = (float)b / 255.0f;
                int num_visible = 0;
                int img, key;
                float x, y;
                fscanf(file, "%d", &num_visible);
                for (int j = 0; j < num_visible; j++)
                {
                    fscanf(file, " %d %d %f %f", &img, &key, &x, &y);
                }
                i += 3;
            }
            fclose(file);
        }
        else
        {
            printf("File can not be opened!\n");
        }
    }
    else
    {
        printf("File does not have a .out extension!");
    }
    return 0;
}

void OutFile::ChangeCameraMode()
{
    for(int i = 0; i < m_nCamera; i++)
    {
        m_pCameras[i].ChangeMode();
    }
}

void OutFile::OpenTexture2d()
{
    if(!m_pTextures)
    {
        m_pTextures = (unsigned int*)malloc(m_nCamera * sizeof(unsigned int));
        glGenTextures(m_nCamera, m_pTextures);
        for(int i = 0; i < m_nCamera; i++)
        {
            m_pCameras[i].InitTexture(m_pTextures[i]);
        }
    }
}

void OutFile::Draw()
{
    //glPushMatrix();
    //glTranslatef(2.0f, 0.0f, 0.0f);
    //glPopMatrix();
    if(m_bTex)
    {
        OpenTexture2d();
    }
    for(int i = 0; i < m_nCamera; i++)
    {
        m_pCameras[i].Draw();
    }
    glPushMatrix();
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, m_pColors);
    glVertexPointer(3, GL_FLOAT, 0, m_pVertices);
    glPointSize(1.0f);
    //glDrawArrays(GL_POINTS, 0, vertexNumber);    // another way
    glBegin(GL_POINTS);
    for(int i = 0; i < m_nVertex; i++)
    {
        glArrayElement(i);
    }
    glEnd();
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}
