/******************************************************************************
**
** @file
** MainForm.qml
** @brief
** VOD配置器主页面
** @author
** panxf
** @date
** 2017-4-18
**
******************************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.3


Rectangle { // 组件根对象
	id: rectRoot
	anchors.fill: parent

	property alias mouseArea: mouseArea

	MouseArea { // 鼠标经过时
		id: mouseArea
		anchors.fill: parent
	}

	StackView { // 实现界面切换
		id: stackView
		initialItem: mainView
		anchors.fill: parent
	}

	Component { // 主界面
		id: mainView
		MainPage { // 主界面配置
			id: mainPage
		}
	}


	Component { // 机顶盒界面
		id: stb
		STBPage { // 机顶盒界面
			id: stbPage
		}
	}

	Component { //智能灯光界面
		id: lamplight
		LamplightPage {
			id: lamplightPage
		}
	}




}
