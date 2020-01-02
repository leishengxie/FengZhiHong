/******************************************************************************
**
** @file
** LCheckBox.qml
** @brief
** 自定义一个CheckBox
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0

Rectangle { //box边框
    id: rectBox
    width: 28
    height: 28
    border.width: 2
    border.color: "black"
    property bool isChecked: false
    signal clicked

    Image { //图片
        id: img
        source: "images/checkIcon.png"
        anchors.centerIn: parent
        visible: rectBox.isChecked ? true : false
    }

    MouseArea { //鼠标区域
        anchors.fill: parent
        onClicked: {
            rectBox.clicked()
        }
    }
}

