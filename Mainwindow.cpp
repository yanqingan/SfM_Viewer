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

#include <QFileDialog>
#include <QMessageBox>
#include "Mainwindow.h"
#include "ui_Mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    m_mainPlane = new QWidget;
    m_sightExplorer = new SightExplorer;
    setCentralWidget(m_sightExplorer);
    CreateActions();
    CreateMenus();
    setGeometry(50, 50, WINDOW_WIDTH, WINDOW_HEIGHT);
    setMinimumSize(WINDOW_WIDTH_MIN, WINDOW_HEIGHT_MIN);
    setWindowTitle("Sight Explorer");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_sightExplorer;
    m_sightExplorer = NULL;
}

void MainWindow::CreateMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newProjectAct);
    m_fileMenu->addAction(m_importPlyAct);
    m_fileMenu->addAction(m_importOutAct);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAct);
    menuBar()->addSeparator();
    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutAct);
}

void MainWindow::NewProject()
{
    m_sightExplorer->ClearSight();
}

void MainWindow::ImportPly()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Import ply files"), ".", tr("Ply Files(*.ply)"));
    if(fileNames.length())
    {
        m_sightExplorer->LoadPlyFiles(fileNames, (int)fileNames.length());
    }
}

void MainWindow::ImportOut()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Import Out files"), ".", tr("Out Files(*.out)"));
    if(fileNames.length())
    {
        m_sightExplorer->LoadOutFiles(fileNames, (int)fileNames.length());
    }
}

void MainWindow::About()
 {
     QMessageBox::about(this, tr("About SightViewer"), tr("The <b>SightViewer</b> made by Qingan Yan."));
 }

void MainWindow::CreateActions()
{
    m_newProjectAct = new QAction(QIcon("../yan-SightExplorer12-C-v1/icons/new.png"), tr("&New Project"), this);
    m_newProjectAct->setShortcut(QKeySequence::New);
    connect(m_newProjectAct, SIGNAL(triggered()), this, SLOT(NewProject()));

    m_importPlyAct = new QAction(QIcon("../yan-SightExplorer12-C-v1/icons/open.png"), tr("Import &Ply Files"), this);
    m_importPlyAct->setShortcut(QKeySequence::New);
    connect(m_importPlyAct, SIGNAL(triggered()), this, SLOT(ImportPly()));

    m_importOutAct = new QAction(QIcon("../yan-SightExplorer12-C-v1/icons/open.png"), tr("Import &Out Files"), this);
    m_importOutAct->setShortcut(QKeySequence::New);
    connect(m_importOutAct, SIGNAL(triggered()), this, SLOT(ImportOut()));

    m_exitAct = new QAction(QIcon(""), tr("&Exit"), this);
    m_exitAct->setShortcut(QKeySequence::New);
    connect(m_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    m_aboutAct = new QAction(QIcon(""), tr("&About"), this);
    m_aboutAct->setShortcut(QKeySequence::New);
    connect(m_aboutAct, SIGNAL(triggered()), this, SLOT(About()));
}
