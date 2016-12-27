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

#include "Quaternion.h"

Quaternion::Quaternion()
{
    x = 0.0;
    y = 0.0;
    z = 0.0;
    w = 0.0;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}


Quaternion::~Quaternion()
{

}

float Quaternion::Norm_2()
{
    return (x * x + y * y + z * z + w * w);
}

void Quaternion::operator =(Vector3f ve)
{
    this->x = ve.x;
    this->y = ve.y;
    this->z = ve.z;
    w = 0.0;
}

