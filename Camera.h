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

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    Camera();
    ~Camera();
    inline bool GetFlag(){ return m_bFlag; }
    inline void SetFlag(bool flag){ m_bFlag = flag; }
    inline int GetId(){ return m_id; }
    inline void SetId(int id){ m_id = id; }
    int InitTexture(int texture);
    void ChangeMode();
    void Draw();

    float R[9];
    float t[3];
    float f;
    float k[2];

private:
    void ShowFramework();
    int ShowThumbnail();


    float m_nWidth;
    float m_nHeight;
    float m_nDepth;
    int m_showMode;
    bool m_bFlag;
    bool m_bLoad;
    int m_id;
    unsigned int m_texture;

};

#endif    // CAMERA_H
