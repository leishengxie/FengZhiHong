QT       += core gui \
    widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets-private

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Component.cpp \
    ComponentMimeData.cpp \
    ComponentTreeModel.cpp \
    ComponentTreeView.cpp \
    GraphicsFlowScene.cpp \
    GraphicsFlowView.cpp \
    GraphicsIOItem.cpp \
    Node.cpp \
    NodeFactory.cpp \
    main.cpp \
    mainwindow.cpp \
    GraphicsNodeItem.cpp

HEADERS += \
    Component.h \
    ComponentMimeData.h \
    ComponentTreeModel.h \
    ComponentTreeView.h \
    GraphicsFlowScene.h \
    GraphicsFlowView.h \
    GraphicsIOItem.h \
    Node.h \
    NodeFactory.h \
    mainwindow.h \
    GraphicsNodeItem.h

FORMS += \
    mainwindow.ui



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
