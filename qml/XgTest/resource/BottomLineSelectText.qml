/******************************************************************************
**
** @file
** BottomLineSelectText.qml
** @brief
** 变形后的带下划线的下拉控件
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.3

Rectangle { //控件区域
	id: rectBottomSelect
	width: 390
	height: 45
	property bool isHLine: true
	property string strName: ""
	property int nCurrentIndex: 0
	property variant model
	property int nOrgin: 180
	property alias comboTextRole: combo.textRole
	property alias comboModel: combo.model
	signal comboSelectChaged(int nIndexChage)

	Text { //选项名称
		id: textName
		anchors.right: orginPoint.left
		anchors.rightMargin: 20
		anchors.verticalCenter: parent.verticalCenter
		text: strName
		font.pixelSize: 20
	}

	ComboBoxStyle { //ComboBox
		id: combo
		anchors.left: orginPoint.right
		anchors.leftMargin: 14
		anchors.right: parent.right
		anchors.rightMargin: 10
		anchors.verticalCenter: parent.verticalCenter
		height: textName.height
		model: rectBottomSelect.model
		visible: count == 1 ? false : true
		currentIndex: nCurrentIndex
		property bool isFristChanged: true
		onCurrentTextChanged: {
			if (isFristChanged) {
				isFristChanged = false
				return
			}
			rectBottomSelect.comboSelectChaged(currentIndex)
		}
	}

	TextInput {
		anchors.left: orginPoint.right
		anchors.leftMargin: 20
		anchors.right: parent.right
		anchors.rightMargin: 10
		anchors.verticalCenter: parent.verticalCenter
		height: textName.height
		text: rectBottomSelect.model[0]
		visible: combo.count == 1 ? true : false
		readOnly: isHLine ? false : true
		clip: true
		selectByMouse: true
		font.pixelSize: 20
	}

	Rectangle { //下划线
		id: rectHLine
		height: 2
		anchors.right: parent.right
		anchors.left: orginPoint.left
		anchors.top: textName.bottom
		anchors.topMargin: 2
		color: "black"
		visible: isHLine ? true : false
	}

	Rectangle { //下划线起始端点
		id: orginPoint
		height: 4
		width: 2
		color: "black"
		anchors.bottom: rectHLine.bottom
		x: nOrgin
		visible: isHLine ? true : false
	}

	Rectangle { //下划线结束端点
		height: 4
		width: 2
		color: "black"
		anchors.bottom: rectHLine.bottom
		anchors.right: parent.right
		visible: isHLine ? true : false
	}
}

