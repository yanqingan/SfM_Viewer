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

#ifndef PLYFILE_H
#define PLYFILE_H

class PlyFile
{

public:
    PlyFile();
    ~PlyFile();
    int Load(const char *filename);
    void Draw();

public:
    float* m_pVertices;
    float* m_pColors;
    int m_nVertex;
};

#endif // PLYFILE_H
