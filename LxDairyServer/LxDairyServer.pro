

QT += core gui network sql

TEMPLATE = app
CONFIG += console

TARGET = LxDairyServer

DESTDIR = $$PWD/bin

win32:CONFIG(release, debug|release): {
QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\" #以管理员运行
QMAKE_LFLAGS += /SUBSYSTEM:WINDOWS,\"5.01\" #VS2013 在XP运行
}
else:win32:CONFIG(debug, debug|release): {

}


#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include


#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool


#import path to system
SRC = ./src
INCLUDEPATH += \
    $$SRC \
    $$SRC/stdc \
    $$SRC/network/http \
    $$SRC/network/http/responder \
    $$SRC/utils


HEADERS += \
    src/stdc/HttpParser.h \
    src/utils/extractvalue.h \
    src/utils/formatHelper.h \
    src/utils/networkAccessHelper.h \
    src/utils/LLogger.h \
    src/utils/LAsyncLogger.h \
    src/network/http/LHttpConfig.h \
    src/network/http/LHttpRequest.h \
    src/network/http/LHttpServer.h \
    src/network/http/LHttpConnection.h \
    src/network/http/LHttpResponse.h \
    src/network/http/LHttpWorker.h \
    src/network/http/responder/LDumpResponder.h \
    src/network/http/responder/LDefaultResponder.h \
    src/network/http/IResponder.h \
    src/network/http/LHttpCookie.h \
    src/network/http/LHttpEvent.h \
    src/network/http/LHttpDef.h \
    src/network/LNetDef.h \
    src/network/http/LResponderFactory.h \
    src/network/http/IResponderCreator.h \
    src/LDiaryResponderCreator.h \
    src/LDairyService.h \
    src/diary_responder/LJokeResponder.h \
    src/SqlOperate.h \
    src/LDairyApp.h

SOURCES += \
    src/main.cpp \
    src/utils/networkAccessHelper.cpp \
    src/utils/LLogger.cpp \
    src/utils/LAsyncLogger.cpp \
    src/network/http/LHttpConfig.cpp \
    src/network/http/LHttpRequest.cpp \
    src/network/http/LHttpServer.cpp \
    src/network/http/LHttpConnection.cpp \
    src/network/http/LHttpResponse.cpp \
    src/network/http/LHttpWorker.cpp \
    src/network/http/responder/LDumpResponder.cpp \
    src/network/http/responder/LDefaultResponder.cpp \
    src/network/http/IResponder.cpp \
    src/network/http/LHttpCookie.cpp \
    src/network/http/LHttpEvent.cpp \
    src/network/http/LHttpDef.cpp \
    src/network/http/LResponderFactory.cpp \
    src/network/http/IResponderCreator.cpp \
    src/LDiaryResponderCreator.cpp \
    src/LDairyService.cpp \
    src/diary_responder/LJokeResponder.cpp \
    src/SqlOperate.cpp \
    src/LDairyApp.cpp


include(qtservice/qtservice.pri)
include(logging/logging.pri)
include($$PWD/../LxDairy/src/src_net_appointments.pri)
