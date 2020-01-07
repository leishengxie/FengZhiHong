import QtQuick 2.4
import QtQuick.Layouts 1.3

Rectangle {
    id: rectDairyEdit
    width: 240
    height: 400
    property alias mouseAreaUpload: mouseAreaUpload
    property alias strTitle: lineInputTitle.text
    property alias strContent: textEditContent.text

    ColumnLayout {
        id: columnLayout1
        spacing: 0
        anchors.fill: parent

        Rectangle {
            id: rectangle1
            width: 200
            height: 50
            color: "#ffffff"
            Layout.fillWidth: true

            LineInput {
                id: lineInputTitle
                anchors.verticalCenter: parent.verticalCenter
                //font.pixelSize: 12
                placeholderText: "请输入标题"
            }
        }

        TextEdit {
            id: textEditContent
            width: 80
            height: 20
            text: qsTr("Text Edit")
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pixelSize: 12
        }

        Rectangle {
            id: rectangle2
            width: 200
            height: 50
            color: "#ffffff"
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
                    text: qsTr("上传")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 16
                }

                MouseArea {
                    id: mouseAreaUpload
                    anchors.fill: parent
                }
            }
        }
    }
}
