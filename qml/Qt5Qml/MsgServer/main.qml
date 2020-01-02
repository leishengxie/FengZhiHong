/******************************************************************************
**
** @file
** main.qml
** @brief
** 主界面配置
** @author
** leisx
** @date
** 2017-3-21
**
******************************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import msg.qt.qQmlManger 1.0

ApplicationWindow {
    id:mainWindow
    title: qsTr("MsgServer")
    width: 800
    height: 480
    visible: true


    Rectangle { // 主窗口客户区
        anchors.fill: parent
        QQmlManger { // 消息内容管理
            id: qmlManger
            objectName: "manger"
            Component.onCompleted: qmlManger.onMyselfCompleted();
        }

        //        StackView {
        //                        id: stackContent
        //                        initialItem: view
        //                        anchors.fill: parent
        //                        Component {
        //                            id: view
        //                            ListView {
        //                                id: lstContent
        //                                objectName: "lstMsg"
        //                                anchors.fill: parent
        //                                delegate: appDelegate
        //                                model:msgModel
        //                                onCountChanged: stackContent.push(view)
        //                            }

        //                        }

        //                    }

        //        Rectangle {
        //            Component {
        //                id: appDelegate
        //                Item {
        //                    width: lstContent.width
        //                    height: 50
        //                    Text {
        //                        text: content
        //                        anchors.verticalCenter: parent.verticalCenter
        //                    }

        //                }
        //            }
        //        }

        id: rectGround
        color: "#729FCF"
        width: parent.width * 0.96
        height: parent.height * 0.86
        x: parent.width * 0.02
        y: parent.width * 0.02
        border.width: 1
        border.color: "#5f5858"

        Text { // 显示消息来源地址
            id: textFrom
            text: qmlManger.text
            anchors.top: parent.top
            font {
                family: "Times"
                pixelSize: 22
                capitalization: Font.AllUppercase
            }
        }

        Text { // 显示消息内容
            id: textContent
            text: qmlManger.content
            anchors.centerIn: parent
            font {
                family: "Times"
                pixelSize: 22
                capitalization: Font.AllUppercase
            }
        }



        RectMsgBtn { // 显示上一条消息按钮
            id: btnLast
            color: rectGround.color
            anchors.left:rectGround.left;
            anchors.topMargin: rectGround.y * 0.5
            anchors.top:rectGround.bottom;
            height: mainWindow.height - rectGround.height - rectGround.y * 2;
            width: height * 3
            text: qsTr("上一条")

            onClicked: {
                qmlManger.lastContent();
            }
        }

        RectMsgBtn { // 显示下一条消息按钮
            id: btnNext
            color: rectGround.color
            anchors.top : btnLast.top
            anchors.leftMargin: btnLast.x
            anchors.left: btnLast.right
            height: btnLast.height
            width: btnLast.width
            text: qsTr("下一条")

            onClicked: {
                qmlManger.nextContent();
            }
        }
    }
}
