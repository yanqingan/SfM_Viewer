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

#ifndef MATRIXNT_H
#define MATRIXNT_H

class Matrix3f;

class Matrix4f
{
public:
    Matrix4f();
    ~Matrix4f();
    void SetIndentify();
    void operator =(Matrix3f mat);

    float m_mat[16];
};

class Matrix3f
{
public:
    Matrix3f();
    ~Matrix3f();
    void SetIndentify();
    void operator =(Matrix3f mat);
    void RightProduct_cm(Matrix3f mat);

    float m_mat[9];
};

#endif    // MATRIXNT_H
