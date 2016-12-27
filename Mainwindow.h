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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SightExplorer.h"

class QAction;
class QMenu;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void NewProject();
    void ImportPly();
    void ImportOut();
    void About();
    
private:
    void CreateActions();
    void CreateMenus();

    QMenu *m_fileMenu;
    QMenu *m_helpMenu;
    QAction *m_newProjectAct;
    QAction *m_importPlyAct;
    QAction *m_importOutAct;
    QAction *m_aboutAct;
    QAction *m_exitAct;
    Ui::MainWindow *ui;
    QWidget *m_mainPlane;
    SightExplorer *m_sightExplorer;
};

#endif // MAINWINDOW_H
