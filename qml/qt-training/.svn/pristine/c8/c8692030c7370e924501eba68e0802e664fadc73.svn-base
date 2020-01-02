/******************************************************************************
**
** @file
** CustomTab.qml
** @brief
** 自定义tab
** @author
** leisx
** @date
** 2017-4-12
**
******************************************************************************/
import QtQuick 2.0

Item {
    id: tabWidget

    default property alias content: stack.children

    property int current: 0
    property int titleWidth: 0
    property bool isShareItem: false

    onCurrentChanged: setOpacities()
    Component.onCompleted: setOpacities()

    function setOpacities() {
        //add 2017-4-7
        if(isShareItem) {
            for (var i = 0; i < stack.children.length; ++i) {
                stack.children[i].opacity = (i == 0 ? 1 : 0)
            }
            return
        }

        for (var i = 0; i < stack.children.length; ++i) {
            stack.children[i].opacity = (i == current ? 1 : 0)
        }
    }

    Rectangle {
        id: rectBg
        anchors.fill: parent
        radius: 20
        color: "#419AF1"
        border.width: 2
        border.color: "white"
    }

    Rectangle {
        id: headerBg
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.top: parent.top
        anchors.topMargin: 2
        height: 36
        color: "#395FAA"
        radius: 6
    }

    Row {
        id: header
        anchors.fill: headerBg
        anchors.leftMargin: 1
        anchors.rightMargin: 1
        Repeater {
            model: stack.children.length
            delegate: Rectangle {
                width: titleWidth == 0 ? header.width / stack.children.length : titleWidth;
                height: parent.height
                color: tabWidget.current == index ? "#6196FC" : "#395FAA"
                radius: 10

                Text {
                    horizontalAlignment: Qt.AlignHCenter; verticalAlignment: Qt.AlignVCenter
                    anchors.fill: parent
                    text: stack.children[index].title
                    elide: Text.ElideRight
                    font.bold: tabWidget.current == index
                    font.pixelSize: 20
                    color: "white"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: tabWidget.current = index
                }
            }
        }
    }

    Item {
        id: stack
        anchors.top: header.bottom;
        anchors.bottom: tabWidget.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.margins: 4
    }
}
