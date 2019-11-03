#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:52:35
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++11

TARGET = LxDairy
TEMPLATE = app
DESTDIR = $$PWD/bin
message("hello LxDairy!")

RC_FILE += icon.rc
RC_FILE += version.rc

RESOURCES += \
    res.qrc

#VERSION = 0.1.1
#QMAKE_TARGET_PRODUCT = LxDairy
#QMAKE_TARGET_COMPANY = Lx
#QMAKE_TARGET_DESCRIPTION = 个人日记#
#QMAKE_TARGET_COPYRIGHT = Lx

#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdToold
else:unix: LIBS += -L$$PWD/../../LxTool/LStdTool/bin/ -lLStdTool

win32: LIBS += -L$$PWD/../../LxMultimedia/LxTTS/lib/ -lTTS_Win32


#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LStdTool/include
DEPENDPATH += $$PWD/../../LxTool/LStdTool/include
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include
INCLUDEPATH += $$PWD/../../LxMultimedia/LxTTS/include
DEPENDPATH += $$PWD/../../LxMultimedia/LxTTS/include

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
    src/delegate/DairyDateDelegate.h \
    src/DairyEdit.h \
    src/DairyEditWidget.h \
    src/model/DairyStatisticsModel.h \
    src/delegate/DairyStatisticsDelegate.h \
    src/model/PrivateMenuModel.h \
    src/model/APasswdTableModel.h \
    src/tts/TTS.h \
    src/tts/windows/LWindowsTTSS.h \
    src/MusicSettingDialog.h \
    src/music/LLrc.h \
    src/music/LLrcWidget.h \
    src/music/LMusicPlayer.h

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
    src/delegate/DairyDateDelegate.cpp \
    src/DairyEdit.cpp \
    src/DairyEditWidget.cpp \
    src/model/DairyStatisticsModel.cpp \
    src/delegate/DairyStatisticsDelegate.cpp \
    src/model/PrivateMenuModel.cpp \
    src/model/APasswdTableModel.cpp \
    src/tts/TTS.cpp \
    src/tts/windows/LWindowsTTS.cpp \
    src/MusicSettingDialog.cpp \
    src/music/LLrc.cpp \
    src/music/LLrcWidget.cpp \
    src/music/LMusicPlayer.cpp

FORMS += \
    src/AboutDialog.ui \
    src/DairyMainWindow.ui \
    src/LoginWidget.ui \
    src/RegisterDialog.ui \
    src/SkinWidget.ui \
    src/DairyEditWidget.ui \
    src/MusicSettingDialog.ui


