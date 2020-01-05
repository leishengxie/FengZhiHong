TEMPLATE = app

QT += qml quick
CONFIG += c++11

SOURCES += main.cpp \
    DairyListModel.cpp \
    ModelManager.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
include($$PWD/../LxDairy/src/src_android.pri)

HEADERS += \
    DairyListModel.h \
    ModelManager.h
