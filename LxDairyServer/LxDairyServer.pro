

QT += core gui network

TEMPLATE = app

TARGET = LxDairyServer

#import path to system
SRC = ./src
INCLUDEPATH += \
    $$SRC \
    $$SRC/stdc \
    $$SRC/responder \
    $$SRC/utils

HEADERS += \
    src/stdc/HttpParser.h \
    src/utils/extractvalue.h \
    src/utils/formatHelper.h \
    src/utils/networkAccessHelper.h \
    src/utils/LLogger.h \
    src/utils/LAsyncLogger.h \
    src/LHttpConfig.h \
    src/LHttpRequest.h \
    src/LHttpServer.h \
    src/LHttpConnection.h \
    src/LHttpResponse.h \
    src/LHttpWorker.h \
    src/LResponderFactory.h \
    src/responder/LDumpResponder.h \
    src/responder/LDefaultResponder.h \
    src/IResponder.h \
    src/LHttpCookie.h \
    src/LHttpEvent.h \
    src/LHttpDef.h

SOURCES += \
    src/main.cpp \
    src/utils/networkAccessHelper.cpp \
    src/utils/LLogger.cpp \
    src/utils/LAsyncLogger.cpp \
    src/LHttpConfig.cpp \
    src/LHttpRequest.cpp \
    src/LHttpServer.cpp \
    src/LHttpConnection.cpp \
    src/LHttpResponse.cpp \
    src/LHttpWorker.cpp \
    src/LResponderFactory.cpp \
    src/responder/LDumpResponder.cpp \
    src/responder/LDefaultResponder.cpp \
    src/IResponder.cpp \
    src/LHttpCookie.cpp \
    src/LHttpEvent.cpp \
    src/LHttpDef.cpp
