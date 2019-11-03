#-------------------------------------------------
#
# Project created by QtCreator 2018-10-11T09:55:18
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxUp_date
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    LHttpClient.cpp \
    LXmlOperate.cpp \
    LVersion.cpp \
    LHttpDownload.cpp \
    LFileSysOperate.cpp


HEADERS  += mainwindow.h \
    LHttpClient.h \
    LXmlOperate.h \
    LVersion.h \
    LHttpDownload.h \
    LFileSysOperate.h


FORMS    += mainwindow.ui


MYDIR = ../bin         # 变量MYDIR指定目标文件生成目录
DESTDIR = $$MYDIR               # 目标文件目录

