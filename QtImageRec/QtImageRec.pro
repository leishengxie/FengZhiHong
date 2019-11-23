QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

DESTDIR = $$PWD/bin

#INCLUDEPATH += -I/usr/local/include
#LIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc

INCLUDEPATH += $$PWD/thirdParty/opencv/include

LIBS += -L$$PWD/thirdParty/opencv/x86/mingw/lib/ -llibopencv_core320.dll \
                                                -llibopencv_ml320.dll \
                                                -llibopencv_highgui320.dll \
                                                -llibopencv_imgcodecs320.dll \
                                                -llibopencv_imgproc320.dll


SOURCES += \
    main.cpp \
    bwlabel.cpp \
    CommonInterface.cpp \
    ImageProcess.cpp \
    ImgSegAlg.cpp \
    MorOperationAlg.cpp \
    TextRec.cpp \
    ImageWidget.cpp \
    ProcessThread.cpp

HEADERS += \
    bwlabel.h \
    CommonInterface.h \
    CommonStruct.h \
    ImageProcess.h \
    ImgSegAlg.h \
    MorOperationAlg.h \
    TextRec.h \
    ImageWidget.h \
    ProcessThread.h


FORMS += \
    widget.ui

RESOURCES +=

