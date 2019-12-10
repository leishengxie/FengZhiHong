#-------------------------------------------------
#
# Project created by QtCreator 2019-08-25T14:52:35
#
#-------------------------------------------------

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG  += c++11

TARGET = LxDairy
TEMPLATE = app
DESTDIR = $$PWD/bin
message("hello LxDairy!")

RESOURCES += \
    res.qrc

#it must be only one .rc file. if has no one, it will create one in build path
#RC_FILE += icon.rc
#RC_FILE += version.rc
RC_ICONS = "img/appIcon/app.ico"
VERSION = 0.1.0.0
QMAKE_TARGET_PRODUCT = LxDairy
QMAKE_TARGET_COMPANY = Lx
QMAKE_TARGET_DESCRIPTION = this is a personal diary
# 版权信息
QMAKE_TARGET_COPYRIGHT = Lx
# 中文（简体）
RC_LANG = 0x0004

#链接#
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtToold
else:unix: LIBS += -L$$PWD/../../LxTool/LQtTool/bin/ -lLQtTool

win32: LIBS += -L$$PWD/../../LxMultimedia/LxTTS/lib/ -lTTS_Win32

#copy dll
win32{
# PRE_TARGETDEPS:The target will run before build
# PRE_TARGETDEPS
copy_deps.target=copy_lqttool
copy_deps.depends=FORCE
copy_deps.commands = copy $$PWD/../../LxTool/LQtTool/bin/LQtTool.dll $$PWD/bin && \
                     copy $$PWD/../../LxMultimedia/LxTTS/lib/TTS_Win32.dll $$PWD/bin
# POST_TARGETDEPS:The target will run after build finished
POST_TARGETDEPS += copy_lqttool
QMAKE_EXTRA_TARGETS += copy_deps
}

#replace/ to \
win32 {
    copy_deps.commands ~= s,/,\\\\,g
}

#win32 { #
#    #src_dir = $$PWD\Resources\*.*
#    CONFIG(debug, debug|release) {
#        dst_dir = $$OUT_PWD\\..\\bin\\
#        #dst_dir = $$OUT_PWD\\debug\\Resources\\
#    } else {
#        dst_dir = $$OUT_PWD\\..\\bin\\
#        #dst_dir = $$OUT_PWD\\release\\Resources\\
#    }

#    # Replace slashes in paths with backslashes for Windows
#    #src_dir ~= s,/,\\,g
#    dst_dir ~= s,/,\\,g

#    #!exists($$dst_dir):system(xcopy $$src_dir $$dst_dir /y /e)
#}

#依赖头文#
INCLUDEPATH += $$PWD/../../LxTool/LQtTool/include
DEPENDPATH += $$PWD/../../LxTool/LQtTool/include
INCLUDEPATH += $$PWD/../../LxMultimedia/LxTTS/include
DEPENDPATH += $$PWD/../../LxMultimedia/LxTTS/include

INCLUDEPATH += $$PWD/src
DEPENDPATH += $$PWD/src

INCLUDEPATH += \
    src/core \
    src/module_dairy \
    src/module_tool \
    src/module_collection \
    src/music \
    src/styles \
    src/tts


HEADERS += \
    src/core/LBaseWidget.h \
    src/module_tool/GeneralToolsWidget.h \
    src/module_tool/tool_accpasswd_book/AccPasswdWidget.h \
    src/module_tool/tool_accpasswd_book/APasswdTableModel.h \
    src/module_tool/tool_rename/OriginNum.h \
    src/module_tool/tool_rename/RenameWidget.h \
    src/music/LLrc.h \
    src/music/LLrcWidget.h \
    src/music/LMusicPlayer.h \
    src/music/MusicSettingDialog.h \
    src/tts/TTS.h \
    src/tts/windows/LWindowsTTSS.h \
    src/AboutDialog.h \
    src/AwesomeFont.h \
    src/DairyMainWindow.h \
    src/LoginWidget.h \
    src/RegisterDialog.h \
    src/SkinWidget.h \
    src/SqlOperate.h \
    src/TextVerifier.h \
    src/User.h \
    src/core/LEvent.h \
    src/DairyApp.h \
    src/module_collection/CollectionWidget.h \
    src/module_collection/collection_jokebook/StarEditor.h \
    src/module_collection/collection_jokebook/JokebookWidget.h \
    src/module_collection/collection_jokebook/JokeModel.h \
    src/module_collection/collection_jokebook/JokeDelegate.h \
    src/module_dairy/Dairy.h \
    src/module_dairy/DairyWidget.h \
    src/module_dairy/dairy_date/DairyDateDelegate.h \
    src/module_dairy/dairy_date/DairyDateTreeModel.h \
    src/module_dairy/dairy_edit/DairyEdit.h \
    src/module_dairy/dairy_edit/DairyEditWidget.h \
    src/module_dairy/dairy_statistics/DairyStatisticsDelegate.h \
    src/module_dairy/dairy_statistics/DairyStatisticsModel.h \
    src/module_dairy/dairy_tag/DairyTagDelegate.h \
    src/module_dairy/dairy_tag/DairyTagListModel.h \
    src/module_dairy/dairy_statistics/DairyStatisticsWidget.h \
    src/module_dairy/dairy_edit/DairyEditMainWidget.h \
    src/DairyAppStation.h \
    src/module_collection/CollectionModel.h \
    src/module_collection/CollectionDelegate.h \
    src/module_tool/GeneralToolsModel.h \
    src/module_collection/collection_jokebook/JokeEditor.h \
    src/styles/LBronzeStyle.h \
    src/styles/LColorStyle.h \
    src/styles/LGreenNaturalStyle.h \
    src/styles/LIconStyle.h \
    src/styles/LMapleLeafStyle.h \
    src/styles/LQuietStyle.h \
    src/styles/LScholarSpiritStyle.h \
    src/styles/LStyleBase.h \
    src/styles/LTabBarVStyle.h \
    src/styles/LNorwegianWoodStyle.h

SOURCES += \
    src/core/LBaseWidget.cpp \
    src/module_tool/GeneralToolsWidget.cpp \
    src/module_tool/tool_accpasswd_book/AccPasswdWidget.cpp \
    src/module_tool/tool_accpasswd_book/APasswdTableModel.cpp \
    src/module_tool/tool_rename/OriginNum.cpp \
    src/module_tool/tool_rename/RenameWidget.cpp \
    src/music/LLrc.cpp \
    src/music/LLrcWidget.cpp \
    src/music/LMusicPlayer.cpp \
    src/music/MusicSettingDialog.cpp \
    src/tts/TTS.cpp \
    src/tts/windows/LWindowsTTS.cpp \
    src/AboutDialog.cpp \
    src/AwesomeFont.cpp \
    src/DairyMainWindow.cpp \
    src/LoginWidget.cpp \
    src/main.cpp \
    src/RegisterDialog.cpp \
    src/SkinWidget.cpp \
    src/SqlOperate.cpp \
    src/TextVerifier.cpp \
    src/User.cpp \
    src/core/LEvent.cpp \
    src/DairyApp.cpp \
    src/module_collection/CollectionWidget.cpp \
    src/module_collection/collection_jokebook/StarEditor.cpp \
    src/module_collection/collection_jokebook/JokebookWidget.cpp \
    src/module_collection/collection_jokebook/JokeModel.cpp \
    src/module_collection/collection_jokebook/JokeDelegate.cpp \
    src/module_dairy/Dairy.cpp \
    src/module_dairy/DairyWidget.cpp \
    src/module_dairy/dairy_date/DairyDateDelegate.cpp \
    src/module_dairy/dairy_date/DairyDateTreeModel.cpp \
    src/module_dairy/dairy_edit/DairyEdit.cpp \
    src/module_dairy/dairy_edit/DairyEditWidget.cpp \
    src/module_dairy/dairy_statistics/DairyStatisticsDelegate.cpp \
    src/module_dairy/dairy_statistics/DairyStatisticsModel.cpp \
    src/module_dairy/dairy_tag/DairyTagDelegate.cpp \
    src/module_dairy/dairy_tag/DairyTagListModel.cpp \
    src/module_dairy/dairy_statistics/DairyStatisticsWidget.cpp \
    src/module_dairy/dairy_edit/DairyEditMainWidget.cpp \
    src/DairyAppStation.cpp \
    src/module_collection/CollectionModel.cpp \
    src/module_collection/CollectionDelegate.cpp \
    src/module_tool/GeneralToolsModel.cpp \
    src/module_collection/collection_jokebook/JokeEditor.cpp \
    src/styles/LBronzeStyle.cpp \
    src/styles/LColorStyle.cpp \
    src/styles/LGreenNaturalStyle.cpp \
    src/styles/LIconStyle.cpp \
    src/styles/LMapleLeafStyle.cpp \
    src/styles/LQuietStyle.cpp \
    src/styles/LScholarSpiritStyle.cpp \
    src/styles/LStyleBase.cpp \
    src/styles/LTabBarVStyle.cpp \
    src/styles/LNorwegianWoodStyle.cpp

FORMS += \
    src/module_tool/GeneralToolsWidget.ui \
    src/module_tool/tool_accpasswd_book/AccPasswdWidget.ui \
    src/module_tool/tool_rename/RenameWidget.ui \
    src/music/MusicSettingDialog.ui \
    src/AboutDialog.ui \
    src/DairyMainWindow.ui \
    src/LoginWidget.ui \
    src/RegisterDialog.ui \
    src/SkinWidget.ui \
    src/module_dairy/DairyWidget.ui \
    src/module_collection/CollectionWidget.ui \
    src/module_collection/collection_jokebook/JokebookWidget.ui \
    src/module_dairy/dairy_edit/DairyEditWidget.ui \
    src/module_dairy/dairy_statistics/DairyStatisticsWidget.ui \
    src/module_dairy/dairy_edit/DairyEditMainWidget.ui \
    src/module_collection/collection_jokebook/JokeEditor.ui




