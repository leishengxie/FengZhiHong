/******************************************************************************
**
** @file
** TextButton.qml
** @brief
** 文字button
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0

Item { //textButton
    id: itemButton
    height: 50
    width: 60
    signal clicked;
    property string text: ""
    property int anchorsType: 2
    property int leftMargin: 0
    property int rightMargin: 0
    Rectangle { //边框
        id: rectButton
        border.width: 1
        border.color: "white"
        radius: 5
        anchors.verticalCenter: parent.verticalCenter
        height: content.height + 10
        width: content.width + 10
        x: {
            switch (anchorsType)
            {
            case 1: 0
                break;
            case 2: (itemButton.width - width) / 2
                break;
            case 3: itemButton.width - width
                break;
            default:
                break;
            }
        }

        Text { //文字
            id: content
            anchors.centerIn: parent
            color: "#4350F9"
            text: itemButton.text
            font.pixelSize: 15
            MouseArea { //鼠标区域
                anchors.fill: parent
                onClicked: itemButton.clicked()
                onPressed: rectButton.state = "clicked"
                onReleased: rectButton.state = ""
            }
        }

        states: [
            State {　// 设置点击效果
                name: "clicked"
                PropertyChanges {
                    target: rectButton
                    border.color: "#f0f0f0"
                }
            }
        ]
    }

    onLeftMarginChanged: {
        rectButton.x = rectButton.x + leftMargin
    }

    onRightMarginChanged: {
        rectButton.x = rectButton.x - rightMargin
    }
}

