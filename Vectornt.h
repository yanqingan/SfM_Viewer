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

#ifndef VECTORNT_H
#define VECTORNT_H

//class Vectornt
//{
//public:
//    Vectornt();
//};

class Vector2f
{
public:
    Vector2f(){}
    Vector2f(float x, float y);
    ~Vector2f(){}
    void operator =(const Vector2f ve);
    Vector2f operator +(const Vector2f ve);
    Vector2f operator -(const Vector2f ve);

    float x;
    float y;
};

class Vector3f
{
public:
    Vector3f(){}
    Vector3f(float x, float y, float z);
    ~Vector3f(){}
    void operator =(const Vector3f ve);
    Vector3f operator +(const Vector3f ve);
    Vector3f operator -(const Vector3f ve);
    Vector3f CrossProduct(const Vector3f ve);
    float DotProduct(const Vector3f ve);
    void Normalize();
    float Norm_2();
    float x;
    float y;
    float z;
};

class Vector3i
{
public:
    Vector3i(){}
    Vector3i(int x, int y, int z);
    ~Vector3i(){}
    void operator =(const Vector3i ve);
    Vector3i operator +(const Vector3i ve);
    Vector3i operator -(const Vector3i ve);

    int x;
    int y;
    int z;
};

#endif // VECTORNT_H
