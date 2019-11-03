#-------------------------------------------------
#
# Project created by QtCreator 2018-10-25T10:07:40
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TheMain
TEMPLATE = app

MYDIR = ../bin         # 变量MYDIR指定目标文件生成目录
DESTDIR = $$MYDIR               # 目标文件目录

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
