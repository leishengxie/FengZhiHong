#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:52:35
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDairy
TEMPLATE = app
DESTDIR = $$PWD/bin
message("hello LxDairy!")



RESOURCES += \
    res.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool

INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdToold
else:unix: LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdTool

INCLUDEPATH += $$PWD/../../LxTool/LStdTool/include
DEPENDPATH += $$PWD/../../LxTool/LStdTool/include

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

HEADERS += \
    src/delegate/DairyTagDelegate.h \
    src/model/DairyDateTreeModel.h \
    src/model/DairyTagListModel.h \
    src/AboutDialog.h \
    src/AwesomeFont.h \
    src/Dairy.h \
    src/DairyMainWindow.h \
    src/GlobalFunc.h \
    src/LoginWidget.h \
    src/RegisterDialog.h \
    src/SkinWidget.h \
    src/SqlOperate.h \
    src/TextVerifier.h \
    src/User.h \
    src/delegate/DairyDateDelegate.h

SOURCES += \
    src/delegate/DairyTagDelegate.cpp \
    src/model/DairyDateTreeModel.cpp \
    src/model/DairyTagListModel.cpp \
    src/AboutDialog.cpp \
    src/AwesomeFont.cpp \
    src/Dairy.cpp \
    src/DairyMainWindow.cpp \
    src/GlobalFunc.cpp \
    src/LoginWidget.cpp \
    src/main.cpp \
    src/RegisterDialog.cpp \
    src/SkinWidget.cpp \
    src/SqlOperate.cpp \
    src/TextVerifier.cpp \
    src/User.cpp \
    src/delegate/DairyDateDelegate.cpp

FORMS += \
    src/AboutDialog.ui \
    src/DairyMainWindow.ui \
    src/LoginWidget.ui \
    src/RegisterDialog.ui \
    src/SkinWidget.ui
