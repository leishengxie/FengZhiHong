QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR = ..

SOURCES += \
    PluginsManger.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Plugin.h \
    PluginsManger.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# 静态库加载
#LIBS           = -L../plugins -lpnp_basictools

#if(!debug_and_release|build_pass):CONFIG(debug, debug|release) {
#   mac:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)_debug
#   win32:LIBS = $$member(LIBS, 0) $$member(LIBS, 1)d
#}

