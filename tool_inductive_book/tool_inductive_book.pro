#-------------------------------------------------
#
# Project created by QtCreator 2019-11-14T10:19:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tool_inductive_book
TEMPLATE = app

DESTDIR = $$PWD/bin

SOURCES += main.cpp \
    OcrHandleWidget.cpp \
    InductiveBookWidget.cpp \
    ListViewEx.cpp \
    ArticleListModel.cpp \
    CheckButton.cpp \
    screenshot/ScreenWidget.cpp \
    screenshot/ImageLabel.cpp \
    text_extractor/TextExtractor.cpp \
    text_recognition/TextRecognition.cpp

HEADERS  += \
    OcrHandleWidget.h \
    InductiveBookWidget.h \
    ListViewEx.h \
    ArticleListModel.h \
    CheckButton.h \
    screenshot/ScreenWidget.h \
    screenshot/ImageLabel.h \
    text_extractor/TextExtractor.h \
    text_recognition/TextRecognition.h

FORMS    += \
    OcrHandleWidget.ui \
    InductiveBookWidget.ui \
    screenshot/ScreenWidget.ui


#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include

INCLUDEPATH += $$PWD/thirdParty/opencv/include \

INCLUDEPATH += $$PWD/thirdParty/tesseract/include
DEPENDPATH += $$PWD/thirdParty/tesseract/include

INCLUDEPATH += $$PWD/thirdParty/leptonica/include
DEPENDPATH += $$PWD/thirdParty/leptonica/include

#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool

#DEPENDPATH += $$PWD/thirdParty/opencv/include
LIBS += -L$$PWD/thirdParty/opencv/x86/mingw/lib/ -llibopencv_core320.dll -llibopencv_ml320.dll -llibopencv_highgui320.dll \
                                                -llibopencv_imgcodecs320.dll


win32: LIBS += -L$$PWD/thirdParty/tesseract/lib/ -llibtesseract.dll

#win32: LIBS += -L$$PWD/thirdParty/leptonica/lib/ -llibleptonica-1.76.0.dll
win32: LIBS += -L$$PWD/thirdParty/leptonica/lib/ -lliblept.dll

RESOURCES += \
    res.qrc


