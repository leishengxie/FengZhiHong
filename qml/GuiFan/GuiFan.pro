TEMPLATE = app

QT += qml quick widgets declarative

SOURCES += main.cpp \
    bin.c \
    CStandard.cpp \
    QQmlManger.cpp \
    QMybutton.cpp \
    QMyLabel.cpp \
    QMyAnim.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
#include(deployment.pri)


HEADERS += \
    bin.h \
    CStandard.h \
    QQmlManger.h \
    QMybutton.h \
    QMyLabel.h \
    CGlobal.h \
    QMyAnim.h


