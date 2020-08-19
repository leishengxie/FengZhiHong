
TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../pluginTest
TARGET        = $$qtLibraryTarget(ToolA)
DESTDIR       = ../../plugins

#! [0]
# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/plugandpaint/plugins
#INSTALLS += target

#CONFIG += install_ok  # Do not cargo-cult this!


SOURCES += \
    ToolA.cpp \
    ToolAWidget.cpp

HEADERS += \
    ToolA.h \
    ToolAWidget.h

FORMS += \
    ToolAWidget.ui


