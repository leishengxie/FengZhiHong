
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD


INCLUDEPATH += \
    $$PWD/core \
    $$PWD/module_dairy \
    $$PWD/module_tool \
    $$PWD/module_collection \
    $$PWD/music \
    $$PWD/styles \
    $$PWD/net_appointments \
    $$PWD/tts


HEADERS += \
    $$PWD/core/LBaseWidget.h \
    $$PWD/module_tool/GeneralToolsWidget.h \
    $$PWD/module_tool/tool_accpasswd_book/AccPasswdWidget.h \
    $$PWD/module_tool/tool_accpasswd_book/APasswdTableModel.h \
    $$PWD/module_tool/tool_rename/OriginNum.h \
    $$PWD/module_tool/tool_rename/RenameWidget.h \
    $$PWD/music/LLrc.h \
    $$PWD/music/LLrcWidget.h \
    $$PWD/music/LMusicPlayer.h \
    $$PWD/music/MusicSettingDialog.h \
    $$PWD/tts/TTS.h \
    $$PWD/tts/windows/LWindowsTTSS.h \
    $$PWD/AboutDialog.h \
    $$PWD/AwesomeFont.h \
    $$PWD/DairyMainWindow.h \
    $$PWD/LoginWidget.h \
    $$PWD/RegisterDialog.h \
    $$PWD/SkinWidget.h \
    $$PWD/SqlOperate.h \
    $$PWD/TextVerifier.h \
    $$PWD/User.h \
    $$PWD/core/LEvent.h \
    $$PWD/DairyApp.h \
    $$PWD/module_collection/CollectionWidget.h \
    $$PWD/module_collection/collection_jokebook/StarEditor.h \
    $$PWD/module_collection/collection_jokebook/JokebookWidget.h \
    $$PWD/module_collection/collection_jokebook/JokeModel.h \
    $$PWD/module_collection/collection_jokebook/JokeDelegate.h \
    $$PWD/module_dairy/Dairy.h \
    $$PWD/module_dairy/DairyWidget.h \
    $$PWD/module_dairy/dairy_date/DairyDateDelegate.h \
    $$PWD/module_dairy/dairy_date/DairyDateTreeModel.h \
    $$PWD/module_dairy/dairy_edit/DairyEdit.h \
    $$PWD/module_dairy/dairy_edit/DairyEditWidget.h \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsDelegate.h \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsModel.h \
    $$PWD/module_dairy/dairy_tag/DairyTagDelegate.h \
    $$PWD/module_dairy/dairy_tag/DairyTagListModel.h \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsWidget.h \
    $$PWD/module_dairy/dairy_edit/DairyEditMainWidget.h \
    $$PWD/DairyAppStation.h \
    $$PWD/module_collection/CollectionModel.h \
    $$PWD/module_collection/CollectionDelegate.h \
    $$PWD/module_tool/GeneralToolsModel.h \
    $$PWD/module_collection/collection_jokebook/JokeEditor.h \
    $$PWD/styles/LBronzeStyle.h \
    $$PWD/styles/LColorStyle.h \
    $$PWD/styles/LGreenNaturalStyle.h \
    $$PWD/styles/LIconStyle.h \
    $$PWD/styles/LMapleLeafStyle.h \
    $$PWD/styles/LQuietStyle.h \
    $$PWD/styles/LScholarSpiritStyle.h \
    $$PWD/styles/LStyleBase.h \
    $$PWD/styles/LTabBarVStyle.h \
    $$PWD/styles/LNorwegianWoodStyle.h \
    $$PWD/styles/LDarkDevelopStyle.h \
    $$PWD/DairyHttpClient.h \
    $$PWD/module_collection/collection_jokebook/Joke.h \
    $$PWD/net_appointments/NetAppointments.h \
    $$PWD/net_appointments/datastream_type/NetDataStream.h \
    $$PWD/UserInfo.h


SOURCES += \
    $$PWD/core/LBaseWidget.cpp \
    $$PWD/module_tool/GeneralToolsWidget.cpp \
    $$PWD/module_tool/tool_accpasswd_book/AccPasswdWidget.cpp \
    $$PWD/module_tool/tool_accpasswd_book/APasswdTableModel.cpp \
    $$PWD/module_tool/tool_rename/OriginNum.cpp \
    $$PWD/module_tool/tool_rename/RenameWidget.cpp \
    $$PWD/music/LLrc.cpp \
    $$PWD/music/LLrcWidget.cpp \
    $$PWD/music/LMusicPlayer.cpp \
    $$PWD/music/MusicSettingDialog.cpp \
    $$PWD/tts/TTS.cpp \
    $$PWD/tts/windows/LWindowsTTS.cpp \
    $$PWD/AboutDialog.cpp \
    $$PWD/AwesomeFont.cpp \
    $$PWD/DairyMainWindow.cpp \
    $$PWD/LoginWidget.cpp \
    $$PWD/main.cpp \
    $$PWD/RegisterDialog.cpp \
    $$PWD/SkinWidget.cpp \
    $$PWD/SqlOperate.cpp \
    $$PWD/TextVerifier.cpp \
    $$PWD/User.cpp \
    $$PWD/core/LEvent.cpp \
    $$PWD/DairyApp.cpp \
    $$PWD/module_collection/CollectionWidget.cpp \
    $$PWD/module_collection/collection_jokebook/StarEditor.cpp \
    $$PWD/module_collection/collection_jokebook/JokebookWidget.cpp \
    $$PWD/module_collection/collection_jokebook/JokeModel.cpp \
    $$PWD/module_collection/collection_jokebook/JokeDelegate.cpp \
    $$PWD/module_dairy/Dairy.cpp \
    $$PWD/module_dairy/DairyWidget.cpp \
    $$PWD/module_dairy/dairy_date/DairyDateDelegate.cpp \
    $$PWD/module_dairy/dairy_date/DairyDateTreeModel.cpp \
    $$PWD/module_dairy/dairy_edit/DairyEdit.cpp \
    $$PWD/module_dairy/dairy_edit/DairyEditWidget.cpp \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsDelegate.cpp \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsModel.cpp \
    $$PWD/module_dairy/dairy_tag/DairyTagDelegate.cpp \
    $$PWD/module_dairy/dairy_tag/DairyTagListModel.cpp \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsWidget.cpp \
    $$PWD/module_dairy/dairy_edit/DairyEditMainWidget.cpp \
    $$PWD/DairyAppStation.cpp \
    $$PWD/module_collection/CollectionModel.cpp \
    $$PWD/module_collection/CollectionDelegate.cpp \
    $$PWD/module_tool/GeneralToolsModel.cpp \
    $$PWD/module_collection/collection_jokebook/JokeEditor.cpp \
    $$PWD/styles/LBronzeStyle.cpp \
    $$PWD/styles/LColorStyle.cpp \
    $$PWD/styles/LGreenNaturalStyle.cpp \
    $$PWD/styles/LIconStyle.cpp \
    $$PWD/styles/LMapleLeafStyle.cpp \
    $$PWD/styles/LQuietStyle.cpp \
    $$PWD/styles/LScholarSpiritStyle.cpp \
    $$PWD/styles/LStyleBase.cpp \
    $$PWD/styles/LTabBarVStyle.cpp \
    $$PWD/styles/LNorwegianWoodStyle.cpp \
    $$PWD/styles/LDarkDevelopStyle.cpp \
    $$PWD/DairyHttpClient.cpp \
    $$PWD/module_collection/collection_jokebook/Joke.cpp \
    $$PWD/net_appointments/NetAppointments.cpp \
    $$PWD/net_appointments/datastream_type/NetDataStream.cpp \
    $$PWD/UserInfo.cpp


FORMS += \
    $$PWD/module_tool/GeneralToolsWidget.ui \
    $$PWD/module_tool/tool_accpasswd_book/AccPasswdWidget.ui \
    $$PWD/module_tool/tool_rename/RenameWidget.ui \
    $$PWD/music/MusicSettingDialog.ui \
    $$PWD/AboutDialog.ui \
    $$PWD/DairyMainWindow.ui \
    $$PWD/LoginWidget.ui \
    $$PWD/RegisterDialog.ui \
    $$PWD/SkinWidget.ui \
    $$PWD/module_dairy/DairyWidget.ui \
    $$PWD/module_collection/CollectionWidget.ui \
    $$PWD/module_collection/collection_jokebook/JokebookWidget.ui \
    $$PWD/module_dairy/dairy_edit/DairyEditWidget.ui \
    $$PWD/module_dairy/dairy_statistics/DairyStatisticsWidget.ui \
    $$PWD/module_dairy/dairy_edit/DairyEditMainWidget.ui \
    $$PWD/module_collection/collection_jokebook/JokeEditor.ui