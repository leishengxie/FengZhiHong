import QtQuick 2.4
import QtQuick.Layouts 1.3
//import "./com_input"

Rectangle {
    id: rectDairyEdit
    width: 240
    height: 400
    property alias mouseAreaUpload: mouseAreaUpload
    property alias mouseAreaBack: mouseAreaBack
    property alias strTitle: lineInputTitle.text
    property alias strContent: textEditContent.text
    property int did: -1

    ColumnLayout {
        id: columnLayout1
        spacing: 0
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            width: parent.width
            height: 50
            color: "lightgray"
            Layout.fillWidth: true
            RowLayout {
                spacing: 10
                anchors.verticalCenter: parent.verticalCenter
                Text {
                    id: textback
                    text: qsTr(" << ")
                    MouseArea {
                        id:  mouseAreaBack
                        anchors.fill: parent
                    }
                }

                LineInput {
                    id: lineInputTitle
                    //font.pixelSize: 12
                    placeholderText: "请输入标题"
                }
            }
        }

        TextEdit {
            id: textEditContent
            width: 80
            height: 20
            text: qsTr("")
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pixelSize: 12
        }

        Rectangle {
            id: rectangle2
            width: parent.width
            height: 50
            color: "lightgray"
            Layout.fillWidth: true
            Rectangle {
                id: rectangle3
                width: 80
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    id: textUpload
                    text: qsTr("提交")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 18
                }

                MouseArea {
                    id: mouseAreaUpload
                    anchors.fill: parent
                }
            }
        }
    }
}
