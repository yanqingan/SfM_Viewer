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

#include <math.h>
#include "Vectornt.h"

//Vectornt::Vectornt()
//{
//}

Vector2f::Vector2f(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vector2f::operator =(const Vector2f ve)
{
    x = ve.x;
    y = ve.y;
}

Vector2f Vector2f::operator -(const Vector2f ve)
{
    Vector2f temp;
    temp.x = x - ve.x;
    temp.y = y - ve.y;
    return temp;
}

Vector2f Vector2f::operator +(const Vector2f ve)
{
    Vector2f temp;
    temp.x = x + ve.x;
    temp.y = y + ve.y;
    return temp;
}

Vector3f::Vector3f(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3f::operator =(const Vector3f ve)
{
    x = ve.x;
    y = ve.y;
    z = ve.z;
}

Vector3f Vector3f::operator -(const Vector3f ve)
{
    Vector3f temp;
    temp.x = x - ve.x;
    temp.y = y - ve.y;
    temp.z = z - ve.z;
    return temp;
}

Vector3f Vector3f::operator +(const Vector3f ve)
{
    Vector3f temp;
    temp.x = x + ve.x;
    temp.y = y + ve.y;
    temp.z = z + ve.z;
    return temp;
}

Vector3f Vector3f::CrossProduct(const Vector3f ve)
{
    Vector3f temp;
    temp.x = y * ve.z - z * ve.y;
    temp.y = z * ve.x - x * ve.z;
    temp.z = x * ve.y - y * ve.x;
    //temp.Normalize();
    return temp;
}

float Vector3f::DotProduct(const Vector3f ve)
{
    float temp;
    temp = x * ve.x + y * ve.y + z * ve.z;
    return temp;
}

void Vector3f::Normalize()
{
    float sum = 1.0 / (x * x + y * y + z * z);
    x *= sum;
    y *= sum;
    z *= sum;
}

float Vector3f::Norm_2()
{
    return (x * x + y * y + z * z);
}

Vector3i::Vector3i(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3i::operator =(const Vector3i ve)
{
    x = ve.x;
    y = ve.y;
    z = ve.z;
}

Vector3i Vector3i::operator -(const Vector3i ve)
{
    Vector3i temp;
    temp.x = x - ve.x;
    temp.y = y - ve.y;
    temp.z = z - ve.z;
    return temp;
}

Vector3i Vector3i::operator +(const Vector3i ve)
{
    Vector3i temp;
    temp.x = x + ve.x;
    temp.y = y + ve.y;
    temp.z = z + ve.z;
    return temp;
}
