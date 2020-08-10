#-------------------------------------------------
#
# Project created by QtCreator 2020-07-23T21:27:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDailySchedule
TEMPLATE = app


SOURCES += main.cpp\
    DailyScheduleBookListView.cpp \
    DailyScheduleBookModel.cpp \
    DailyScheduleEditor.cpp \
    DailyScheduleListDelegate.cpp \
    DailyScheduleListModel.cpp \
    DailyScheduleListView.cpp \
    DailyScheduleModel.cpp \
    DailyScheduleDelegate.cpp \
    DailyScheduleSqlOperate.cpp \
    DailyScheduleTableView.cpp \
    MiniWidget.cpp \
    StartEndTimeEditor.cpp \
    DailyScheduleWidget.cpp

HEADERS  += \
    DailyScheduleBookListView.h \
    DailyScheduleBookModel.h \
    DailyScheduleEditor.h \
    DailyScheduleListDelegate.h \
    DailyScheduleListModel.h \
    DailyScheduleListView.h \
    DailyScheduleModel.h \
    DailyScheduleDelegate.h \
    DailyScheduleSqlOperate.h \
    DailyScheduleTableView.h \
    MiniWidget.h \
    StartEndTimeEditor.h \
    DailyScheduleWidget.h

FORMS    += \
    DailyScheduleEditor.ui \
    DailyScheduleWidget.ui

RESOURCES += \
    res.qrc

RC_ICONS = "img/appIcon/app.ico"

#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include

#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool


#copy dll
win32{
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

