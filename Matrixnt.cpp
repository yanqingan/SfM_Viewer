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

#include "Matrixnt.h"

Matrix4f::Matrix4f()
{

}

Matrix4f::~Matrix4f()
{

}

void Matrix4f::SetIndentify()
{
    for(int i = 0; i < 4; i++)
    {
        int offset = i * 4;
        for(int j = 0; j < 4; j++)
        {
            if(i == j)
                m_mat[offset + j] = 1.0;
            else
                m_mat[offset + j] = 0.0;
        }
    }
}

void Matrix4f::operator =(Matrix3f mat)
{
    for(int i = 0; i < 3; i++)
    {
        int r1 = i * 4;
        int r2 = i * 3;
        for(int j = 0; j < 3; j++)
        {
            m_mat[r1 + j] = mat.m_mat[r2 + j];
        }
    }
}

Matrix3f::Matrix3f()
{

}

Matrix3f::~Matrix3f()
{

}

void Matrix3f::SetIndentify()
{
    for(int i = 0; i < 3; i++)
    {
        int offset = i * 3;
        for(int j = 0; j < 3; j++)
        {
            if(i == j)
                m_mat[offset + j] = 1.0;
            else
                m_mat[offset + j] = 0.0;
        }
    }
}

void Matrix3f::operator =(Matrix3f mat)
{
    for(int i = 0; i < 9; i++)
    {
        m_mat[i] = mat.m_mat[i];
    }
}

void Matrix3f::RightProduct_cm(Matrix3f mat)
{
    float temp[9];
//    for(int i = 0; i < 3; i++)
//    {
//        int r = i * 3;
//        for(int j = 0; j < 3; j++)
//        {
//            temp[r + j] = 0.0;
//            for(int k = 0; k < 3; k++)
//            {
//                temp[r + j] += m_mat[r + k] * mat.m_mat[k * 3 +j];
//            }
//        }
//    }
    temp[0] = m_mat[0] * mat.m_mat[0] + m_mat[3] * mat.m_mat[1] + m_mat[6] * mat.m_mat[2];
    temp[3] = m_mat[0] * mat.m_mat[3] + m_mat[3] * mat.m_mat[4] + m_mat[6] * mat.m_mat[5];
    temp[6] = m_mat[0] * mat.m_mat[6] + m_mat[3] * mat.m_mat[7] + m_mat[6] * mat.m_mat[8];

    temp[1] = m_mat[1] * mat.m_mat[0] + m_mat[4] * mat.m_mat[1] + m_mat[7] * mat.m_mat[2];
    temp[4] = m_mat[1] * mat.m_mat[3] + m_mat[4] * mat.m_mat[4] + m_mat[7] * mat.m_mat[5];
    temp[7] = m_mat[1] * mat.m_mat[6] + m_mat[4] * mat.m_mat[7] + m_mat[7] * mat.m_mat[8];

    temp[2] = m_mat[2] * mat.m_mat[0] + m_mat[5] * mat.m_mat[1] + m_mat[8] * mat.m_mat[2];
    temp[5] = m_mat[2] * mat.m_mat[3] + m_mat[5] * mat.m_mat[4] + m_mat[8] * mat.m_mat[5];
    temp[8] = m_mat[2] * mat.m_mat[6] + m_mat[5] * mat.m_mat[7] + m_mat[8] * mat.m_mat[8];
    for(int i = 0; i < 9; i++)
    {
        m_mat[i] = temp[i];
    }
}

