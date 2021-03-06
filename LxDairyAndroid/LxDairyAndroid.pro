TEMPLATE = app

QT += qml quick core gui widgets multimedia xml
CONFIG += c++11

# tiao shi
CONFIG+=declarative_debug
CONFIG+=qml_debug
#CONFIG -= qml_debug

QMAKE_CXXFLAGS_RELEASE = $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE = $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

SOURCES += main.cpp \
    DairyListModel.cpp \
    ModelManager.cpp \
    DairyAndroidApp.cpp \
    DairyHttpRequest.cpp \
    DairyGlobalInstance.cpp

RESOURCES += qml.qrc# \
#    img.qrc

RC_FILE += icon.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# add define for android mobile paltform, it use qml for ui.
DEFINES += ANDROID_MOBILE_PALTFORM_QML

#copy dll
win32:CONFIG(release, debug|release): {
# PRE_TARGETDEPS:The target will run before build
# PRE_TARGETDEPS
copy_deps.target=copy_lqttool
copy_deps.depends=FORCE
copy_deps.commands = copy $$PWD/../../LxTool/LQtTool/bin/LQtTool.dll $$PWD/bin
# POST_TARGETDEPS:The target will run after build finished
POST_TARGETDEPS += copy_lqttool
QMAKE_EXTRA_TARGETS += copy_deps
}

#replace/ to \
win32 {
    copy_deps.commands ~= s,/,\\\\,g
}

#依赖头文#
#INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
#DEPENDPATH += $$PWD/../../LxTool/LQtTool/include


##链接#
#win32 {
#    CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
#    CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
#}

#unix {
#    CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
#   CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
#}


# Default rules for deployment.
include(deployment.pri)
include($$PWD/../../../lib/LxTool/LxQt.pri)
include($$PWD/../LxDairy/src/src_android.pri)

HEADERS += \
    DairyListModel.h \
    ModelManager.h \
    DairyAndroidApp.h \
    DairyHttpRequest.h \
    DairyGlobalInstance.h

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
#        $$PWD/../../LxTool/LQtTool/bin/libLQtTool.so
}

DISTFILES += \
    android_src/AndroidManifest.xml \
    android_src/res/values/libs.xml \
    android_src/build.gradle

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android_src



