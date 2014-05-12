#-------------------------------------------------
#
# Project created by QtCreator 2014-03-15T22:19:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperSeller
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    plotchild.cpp \
    mdichild.cpp \
    plotdraw.cpp \
    oracle.cpp \
    histdraw.cpp \
    histchild.cpp \
    gen.cpp

HEADERS  += mainwindow.h \
    mdichild.h \
    plotchild.h \
    plotdraw.h \
    oracle.h \
    histdraw.h \
    histchild.h \
    gen.h
