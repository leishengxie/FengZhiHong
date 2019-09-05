TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp

#RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../imports

# Default rules for deployment.
include(deployment.pri)
#include(core/Button.qml)

DISTFILES += \
    ../main.qml \
    ../core/Button.qml \
    ../core/EditMenu.qml \
    ../core/FileDialog.qml \
    ../core/FileMenu.qml \
    ../core/MenuBar.qml \
    ../core/TextArea.qml \
    ../images/arrow.png
