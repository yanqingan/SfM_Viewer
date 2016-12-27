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
#include <math.h>
#include <string.h>
#include <QGLWidget>
#include "PlyFile.h"

PlyFile::PlyFile()
{
    m_pVertices = NULL;
    m_pColors = NULL;
    m_nVertex = 0;
}

PlyFile::~PlyFile()
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
}

/* mainly use c language */
int PlyFile::Load(const char* filename)
{
    /* whether is a ply file */
    char* pCh = strstr(filename, ".ply");    // return the position
    if(pCh != NULL)
    {
        FILE* file = fopen(filename, "r");
        fseek(file, 0, SEEK_END);    // change the position to read(take care: SEEK_END)
        long fileSize = ftell(file);    // tell the byte size of the pointer from the beginning
        try
        {
            m_pVertices = (float*)malloc(fileSize * sizeof(float));
            m_pColors = (float*)malloc(fileSize * sizeof(float));
        }
        catch(char*)
        {
            printf("Exception in malloc vertex buffer of PlyFile::load()!\n");
            return -1;
        }
        if(m_pVertices == NULL)
            return -1;
        fseek(file, 0, SEEK_SET);    // this is SEEK_SET
        if(file)
        {
            int i = 0;
            char buf[1000];
            fgets(buf, 300, file);   // read (300 - 1) bytes or a line
            /* read header */
            while(strncmp("element vertex", buf, strlen("element vertex")) != 0)    // string comparsion, if equal return 0
            {
                fgets(buf, 300, file);    // read again
            }
            strcpy(buf, buf + strlen("element vertex"));    // copy string from the position of strlen bytes
            sscanf(buf, "%i", &m_nVertex);    // read a format data from a string
            fseek(file, 0, SEEK_SET);    // go to the beginning
            while(strncmp("end_header", buf, strlen("end_header")) != 0)    // find the end of header
            {
                fgets(buf, 300, file);
            }
            /* read vertices and colors */
            i = 0;
            for(int iter = 0; iter < m_nVertex; iter++)
            {
                fgets(buf, 300, file);
                int r, g, b;
                sscanf(buf, "%f %f %f %d %d %d", &m_pVertices[i], &m_pVertices[i + 1]
                        , &m_pVertices[i + 2], &r, &g, &b);    // the first three is positions, latter three is colors
                m_pColors[i] = (float)r / 255;
                m_pColors[i + 1] = (float)g / 255;
                m_pColors[i + 2] = (float)b / 255;
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
        printf("File does not have a .ply extension!");
    }
    return 0;
}

void PlyFile::Draw()
{
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, m_pColors);
    glVertexPointer(3, GL_FLOAT, 0, m_pVertices);
    //glDrawArrays(GL_POINTS, 0, vertexNumber);    // another way
    glBegin(GL_POINTS);
    for(int i = 0; i < m_nVertex; i++)
    {
        glArrayElement(i);
    }
    glEnd();
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
