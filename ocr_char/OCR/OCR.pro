HEADERS += \
    OCR.h

SOURCES += \
    OCR.cpp \
    main.cpp

#引入opencv库
INCLUDEPATH += /opt/opencv_pc/include/
INCLUDEPATH += /opt/opencv_pc/include/opencv
INCLUDEPATH += /opt/opencv_pc/include/opencv2

LIBS += /opt/opencv_pc/lib/*.so*
