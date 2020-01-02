import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id:mainWindow
    title: qsTr("MsgCient")
    width: 800
    height: 480
    visible: true

    //property double marginWidth: mainWindow * 0.02


    Rectangle {
        id:rectGround
        color: "#729FCF"
        width: parent.width * 0.96
        height: parent.height * 0.86
        x: parent.width * 0.02
        y: parent.width * 0.02


        ListView {
            id: lstContent
            anchors.fill: parent
            delegate: appDelegate
            model: ListModel {
                id:contentModel
            }
        }
        Component {
            id: appDelegate
            Item {
                width: lstContent.width
                height: 50
//                Rectangle {
//                    id:cellRect
//                    anchors.fill: parent
//                    border.width: 1
//                    border.color: "#5f5858"
                    Text {
                        text: name
                        anchors.verticalCenter: parent.verticalCenter
                    }
               // }
            }
        }
    }

    RectMsgBtn {
        id: btnLast
        color: rectGround.color
        anchors.left:rectGround.left;
        anchors.topMargin: rectGround.y * 0.5
        anchors.top:rectGround.bottom;
        height: mainWindow.height - rectGround.height - rectGround.y * 2;
        width: height * 3
        text:qsTr("上一条")
        onClicked:
        {

        }
    }

    RectMsgBtn {
        id: btnNext
        color: rectGround.color
        anchors.top : btnLast.top
        anchors.leftMargin: btnLast.x
        anchors.left: btnLast.right
        height: btnLast.height
        width: btnLast.width
        text:qsTr("下一条")
        onClicked:
        {

        }
    }

    RectMsgBtn {
        id: btnAdd
        color: rectGround.color
        anchors.top : btnLast.top
        anchors.leftMargin: btnLast.x
        anchors.left: btnNext.right
        height: btnLast.height
        width: btnLast.width
        text:qsTr("add")
        onClicked:
        {
            contentModel.append({"name":Qt.formatDateTime(new Date(), "dddd yyyy-MM-dd MMM hh:mm:ss")});
        }
    }

}
