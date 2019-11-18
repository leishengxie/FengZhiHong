#-------------------------------------------------
#
# Project created by QtCreator 2019-11-14T10:19:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OCR
TEMPLATE = app

DESTDIR = $$PWD/bin

SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h

FORMS    += widget.ui


#INCLUDEPATH += /usr/local/include/tesseract \
#            /usr/include/leptonica \
#            /usr/local/include/leptonica \
#            /usr/local/include/opencv \
#            /usr/local/include/opencv2

#LIBS += -L/usr/local/lib/ -llept -ltesseract \
#        /usr/local/lib/libopencv_highgui.so \
#        /usr/local/lib/libopencv_core.so    \
#        /usr/local/lib/libopencv_imgproc.so \
#        -lopencv_core -lopencv_imgcodecs -lopencv_highgui


INCLUDEPATH += $$PWD/thirdParty/opencv/include \

INCLUDEPATH += $$PWD/thirdParty/tesseract/include
DEPENDPATH += $$PWD/thirdParty/tesseract/include

INCLUDEPATH += $$PWD/thirdParty/leptonica/include
DEPENDPATH += $$PWD/thirdParty/leptonica/include


#DEPENDPATH += $$PWD/thirdParty/opencv/include
LIBS += -L$$PWD/thirdParty/opencv/x86/mingw/lib/ -llibopencv_core320.dll -llibopencv_ml320.dll -llibopencv_highgui320.dll \
                                                -llibopencv_imgcodecs320.dll




win32: LIBS += -L$$PWD/thirdParty/tesseract/lib/ -llibtesseract.dll



#win32: LIBS += -L$$PWD/thirdParty/leptonica/lib/ -llibleptonica-1.76.0.dll
win32: LIBS += -L$$PWD/thirdParty/leptonica/lib/ -lliblept.dll

