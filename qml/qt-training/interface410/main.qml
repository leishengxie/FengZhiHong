/******************************************************************************
**
** @file
** main.qml
** @brief
** 界面框架定义
** @author
** wenn
** @date
** 2017-3-29
**
******************************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
	title: qsTr("interfaceDeleteSong")
	width: 1300
	height: 600
    visible: true


    MainForm {
        anchors.fill: parent
    }

}
