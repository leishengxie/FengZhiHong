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

DEFINES += LX_DAIRY_APP

RESOURCES += \
    res.qrc

#it must be only one .rc file. if has no one, it will create one in build path
#RC_FILE += icon.rc
#RC_FILE += version.rc
RC_ICONS = "img/appIcon/app.ico"
VERSION = 0.2.0.0
QMAKE_TARGET_PRODUCT = LxDairy
QMAKE_TARGET_COMPANY = Lx
QMAKE_TARGET_DESCRIPTION = this is a personal diary
# 版权信息
QMAKE_TARGET_COPYRIGHT = Lx
# 中文（简体）
RC_LANG = 0x0004

#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include
INCLUDEPATH += $$PWD/../../LxMultimedia/LxTTS/include
DEPENDPATH += $$PWD/../../LxMultimedia/LxTTS/include

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





include($$PWD/src/src.pri)
#include($$PWD/src/src_net_appointments.pri)

