#-------------------------------------------------
#
# Project created by QtCreator 2012-12-13T16:03:18
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SfM_Viewer
TEMPLATE = app


SOURCES += main.cpp\
        Mainwindow.cpp \
    SightExplorer.cpp \
    Matrixnt.cpp \
    Vectornt.cpp \
    Quaternion.cpp \
    PlyFile.cpp \
    OutFile.cpp \
    Camera.cpp

HEADERS  += Mainwindow.h \
    SightExplorer.h \
    Matrixnt.h \
    Vectornt.h \
    Quaternion.h \
    PlyFile.h \
    OutFile.h \
    Camera.h

FORMS    += Mainwindow.ui
