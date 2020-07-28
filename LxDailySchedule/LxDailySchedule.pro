#-------------------------------------------------
#
# Project created by QtCreator 2020-07-23T21:27:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LxDailySchedule
TEMPLATE = app


SOURCES += main.cpp\
    DailyScheduleModel.cpp \
    DailyScheduleDelegate.cpp \
    StartEndTimeEditor.cpp \
    DailyScheduleWidget.cpp

HEADERS  += \
    DailyScheduleModel.h \
    DailyScheduleDelegate.h \
    StartEndTimeEditor.h \
    DailyScheduleWidget.h

FORMS    += \
    DailyScheduleWidget.ui
