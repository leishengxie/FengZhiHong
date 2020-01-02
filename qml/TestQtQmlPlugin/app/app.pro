TEMPLATE = app

QT += qml quick

SOURCES += main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
 QML_IMPORT_PATH = $$PWD/../
# QML_IMPORT_PATH = E:\\qt-work\\Qt5Project

# Default rules for deployment.
include(deployment.pri)
