/******************************************************************************
**
** @file
** main.qml
** @brief
** QML入口
** @author
** panxf
** @date
** 2017-4-18
**
******************************************************************************/

import QtQuick 2.4
import QtQuick.Window 2.2

Window { // 系统窗口
	visible: true
	width: 800
	height: 600
	title: qsTr("迅歌VOD配置")

	MainForm { // 首页
		id: mainForm
		anchors.fill: parent
	}
}
