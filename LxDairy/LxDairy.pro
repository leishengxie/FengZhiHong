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

RESOURCES += \
    res.qrc

#it must be only one .rc file. if has no one, it will create one in build path
#RC_FILE += icon.rc
#RC_FILE += version.rc
RC_ICONS = "img/appIcon/app.ico"
VERSION = 0.1.0.0
QMAKE_TARGET_PRODUCT = LxDairy
QMAKE_TARGET_COMPANY = Lx
QMAKE_TARGET_DESCRIPTION = this is a personal diary
# 版权信息
QMAKE_TARGET_COPYRIGHT = Lx
# 中文（简体）
RC_LANG = 0x0004

#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool

win32: LIBS += -L$$PWD/../../LxMultimedia/LxTTS/lib/ -lTTS_Win32

#copy dll
win32{
# PRE_TARGETDEPS:The target will run before build
# PRE_TARGETDEPS
copy_deps.target=copy_lqttool
copy_deps.depends=FORCE
copy_deps.commands = copy $$PWD/../../LxTool/LQtTool/bin/LQtTool.dll $$PWD/bin && \
                     copy $$PWD/../../LxMultimedia/LxTTS/lib/TTS_Win32.dll $$PWD/bin
# POST_TARGETDEPS:The target will run after build finished
POST_TARGETDEPS += copy_lqttool
QMAKE_EXTRA_TARGETS += copy_deps
}

#replace/ to \
win32 {
    copy_deps.commands ~= s,/,\\\\,g
}

#win32 { #
#    #src_dir = $$PWD\Resources\*.*
#    CONFIG(debug, debug|release) {
#        dst_dir = $$OUT_PWD\\..\\bin\\
#        #dst_dir = $$OUT_PWD\\debug\\Resources\\
#    } else {
#        dst_dir = $$OUT_PWD\\..\\bin\\
#        #dst_dir = $$OUT_PWD\\release\\Resources\\
#    }

#    # Replace slashes in paths with backslashes for Windows
#    #src_dir ~= s,/,\\,g
#    dst_dir ~= s,/,\\,g

#    #!exists($$dst_dir):system(xcopy $$src_dir $$dst_dir /y /e)
#}

#依赖头文#
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
    src/music/LMusicPlayer.h \
    src/tool_rename/OriginNum.h \
    src/tool_rename/RenameWidget.h

SOURCES += \
    src/delegate/DairyTagDelegate.cpp \
    src/model/DairyDateTreeModel.cpp \
    src/model/DairyTagListModel.cpp \
    src/AboutDialog.cpp \
    src/AwesomeFont.cpp \
    src/Dairy.cpp \
    src/DairyMainWindow.cpp \
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
    src/music/LMusicPlayer.cpp \
    src/tool_rename/OriginNum.cpp \
    src/tool_rename/RenameWidget.cpp

FORMS += \
    src/AboutDialog.ui \
    src/DairyMainWindow.ui \
    src/LoginWidget.ui \
    src/RegisterDialog.ui \
    src/SkinWidget.ui \
    src/DairyEditWidget.ui \
    src/MusicSettingDialog.ui \
    src/tool_rename/RenameWidget.ui


