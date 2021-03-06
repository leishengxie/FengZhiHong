import QtQuick 2.12
import QtQuick.Layouts 1.12
//import Qt.labs.controls 1.0
import QtQuick.Controls 2.12
import "./com_input"

Rectangle {
    id: rectDairyEdit
    //width: 240
    //height: 400
    //anchors.fill: parent
    property alias mouseAreaUpload: mouseAreaUpload
    property alias mouseAreaBack: mouseAreaBack
    property alias lineInputTitle: lineInputTitle
    property alias textEditContent: textEditContent
    property alias flick: flick

    property alias strTitle: lineInputTitle.text
    property alias strContent: textEditContent.text
    property int did: -1

    ColumnLayout {
        id: columnMain
        spacing: 0
        anchors.fill: parent

        Rectangle {
            id: rectTop
            width: parent.width
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height*0.08
            color: "lightgray"

            RowLayout {
                anchors.fill: parent
                Rectangle {
                    Layout.preferredHeight: parent.height
                    Layout.preferredWidth: parent.width*0.2
                    color: "lightgray"
                    //anchors.verticalCenter: parent.verticalCenter
                    Text {
                        id: textback
                        text: qsTr("<<")
                        anchors.centerIn: parent

                    }
                    MouseArea {
                        id:  mouseAreaBack
                        anchors.fill: parent
                    }
                }

                MenuTextField {
                    id: lineInputTitle
                    Layout.preferredWidth: parent.width*0.6
                    Layout.preferredHeight: parent.height*0.8
                    placeholderText: "请输入标题"
                    //anchors.verticalCenter: parent.verticalCenter
                }
            }
        }


        Flickable {
            id: flick
            Layout.fillHeight: true
            Layout.fillWidth: true
            contentWidth: textEditContent.paintedWidth
            contentHeight: textEditContent.paintedHeight
            clip: true
            MenuTextArea {
                id: textEditContent
                Layout.fillHeight: true
                Layout.fillWidth: true
                width: flick.width
                height: flick.height
                focus: true
                wrapMode: TextEdit.Wrap
            }
        }

        Rectangle {
            id: rectangleCommit
            Layout.preferredHeight: parent.height*0.08
            color: "lightgray"
            Layout.fillWidth: true
            Rectangle {
                height: parent.height*0.8
                width: height*1.5
                color: "#ffffff"
                anchors.centerIn: parent

                Text {
                    id: textUpload
                    text: qsTr("提交")
                    anchors.centerIn: parent
                }

                MouseArea {
                    id: mouseAreaUpload
                    anchors.fill: parent
                }
            }
        }

    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
