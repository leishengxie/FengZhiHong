TEMPLATE      = lib
CONFIG       += plugin
QT           += widgets
INCLUDEPATH  += ../../LxDairy/src/module_tool
TARGET        = $$qtLibraryTarget(ToolA)
DESTDIR       = ../../LxDairy/bin/plugins

#! [0]
# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/plugandpaint/plugins
#INSTALLS += target

#CONFIG += install_ok  # Do not cargo-cult this!

FORMS += \
    RenameWidget.ui

HEADERS += \
    OriginNum.h \
    RenameWidget.h \
    RenameToolPlugin.h

SOURCES += \
    OriginNum.cpp \
    RenameWidget.cpp \
    RenameToolPlugin.cpp
