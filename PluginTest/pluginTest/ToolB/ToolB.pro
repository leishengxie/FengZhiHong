
TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../pluginTest
TARGET        = $$qtLibraryTarget(ToolB)
DESTDIR       = ../../plugins



SOURCES += \
    ToolB.cpp \
    ToolBWidget.cpp

HEADERS += \
    ToolB.h \
    ToolBWidget.h

FORMS += \
    ToolBWidget.ui


