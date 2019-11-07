
TEMPLATE = app

QT += core gui network

#import path to system
#HTTP = ./http
#INCLUDEPATH += . \
#    $$HTTP \
#    $$HTTP/http-parser \
#    responders \
#    ./utils

HEADERS += \
    stdc/HttpParser.h \
    utils/extractvalue.h \
    utils/formatHelper.h \
    utils/networkAccessHelper.h \
    utils/LLogger.h \
    utils/LAsyncLogger.h \
    LHttpConfig.h \
    LHttpRequest.h \
    LHttpServer.h \
    LHttpConnection.h \
    LHttpResponse.h \
    LHttpWorker.h \
    LResponderFactory.h \
    responder/LDumpResponder.h \
    responder/LDefaultResponder.h \
    IResponder.h \
    LHttpCookie.h \
    LHttpEvent.h \
    LHttpDef.h

SOURCES += \
    main.cpp \
    utils/networkAccessHelper.cpp \
    utils/LLogger.cpp \
    utils/LAsyncLogger.cpp \
    LHttpConfig.cpp \
    LHttpRequest.cpp \
    LHttpServer.cpp \
    LHttpConnection.cpp \
    LHttpResponse.cpp \
    LHttpWorker.cpp \
    LResponderFactory.cpp \
    responder/LDumpResponder.cpp \
    responder/LDefaultResponder.cpp \
    IResponder.cpp \
    LHttpCookie.cpp \
    LHttpEvent.cpp \
    LHttpDef.cpp
