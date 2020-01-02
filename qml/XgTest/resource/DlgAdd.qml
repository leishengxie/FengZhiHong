import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Rectangle {
    id: rectDlg
    width: 252
    height: 153
    property string strTitle
    signal saveTemplateName(string strName)
    property string strTemplateName

    Rectangle {
        id: rectTop
        width: parent.width
        height: 36
        anchors.top: parent.top
        anchors.left: parent.left
        color: "#cccccc"

        Text {
            id: textTitle
            text: strTitle
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 20
            font.pixelSize: 16
        }
        ImgButton {
            height: parent.height
            width: parent.height
            color: "transparent"
            picSrc: "images/close.png"
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            onClicked: {
                dlgFileName = ""
            }
        }
    }

    Rectangle {
        anchors.top: rectTop.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        color: "#f2f2f2"
        Column {
            spacing: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 14
                TextField {
                    id: textField
                    height: 42
                    width: 230
                    placeholderText: "请输入模板名"
                    font.pixelSize: 16
                    style: TextFieldStyle { // 文本框背景样式定义
                        background: Rectangle {
                            radius: 10
                            border.color: "#0078d7"
                            border.width: 1
                        }
                    }
                    onTextChanged: {
                        strTemplateName = text
                    }
                }


            Row {
                id: rowButton
                height: 42
                width: 230
                spacing: 10
                GeneralButton {
                    id: btnCancel
                    text: "取消"
                    onClicked: {
                        dlgFileName = ""
                    }
                }

                GeneralButton {
                    id: btnOK
                    text: "确定"
                    onClicked: {
                        saveTemplateName(strTemplateName)
                        dlgFileName = ""
                    }
                }
            }
        }
    }
}

