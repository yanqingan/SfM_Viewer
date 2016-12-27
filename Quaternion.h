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

#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vectornt.h"

class Quaternion
{
public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    ~Quaternion();
    float Norm_2();
    void operator =(const Vector3f ve);

    float x;
    float y;
    float z;
    float w;
};

#endif // QUATERNION_H
