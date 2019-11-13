#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T13:49:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = FreeRename
#TARGET = 重命名工�TEMPLATE = app

DESTDIR = ../bin

SOURCES += main.cpp\
    OriginNum.cpp \
    RenameWidget.cpp

HEADERS  += \
    OriginNum.h \
    RenameWidget.h

FORMS    += \
    RenameWidget.ui

RC_FILE += icon.rc

win32 { #
    #src_dir = $$PWD\Resources\*.*
    CONFIG(debug, debug|release) {
        dst_dir = $$OUT_PWD\\..\\bin\\
        #dst_dir = $$OUT_PWD\\debug\\Resources\\
    } else {
        dst_dir = $$OUT_PWD\\..\\bin\\
        #dst_dir = $$OUT_PWD\\release\\Resources\\
    }

    # dst_dir 最后的 \\ 是必须的，用来标�xcopy 到一个文件夹，若不存在，创建�
    # Replace slashes in paths with backslashes for Windows
    #src_dir ~= s,/,\\,g
    dst_dir ~= s,/,\\,g

    #!exists($$dst_dir):system(xcopy $$src_dir $$dst_dir /y /e)
    ##system(copy rename.bat $$PWD)
    system(copy rename.bat $$dst_dir)
}

#$$PWD代表的是.pro文件所在路径，所�$PWD表示当前路径，后面跟了我一个依赖库的路�
#$$OUT_PWD代表的是项目的构建路径，也就是输出路径，拷贝在debug文件夹下面所以后面加了一个debug.$$OUT_PWD//..//bin//
