import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 1000
    height: 800
    title:qsTr("重庆云威科技有限公司-云威平台客户端")
    //flags: Qt.Window | Qt.FramelessWindowHint

    header:Rectangle {
        id: tabBar
        height: 100
        color: "#0ba8e6"

        RowLayout{
            height: parent.height
            TextTabButton{
                img: "img/button.png";
                txt: qsTr("全站检测");
                index:0;
            }
            TextTabButton{
                img: "img/button.png";
                txt: qsTr("全站检测");
                index:1;
            }
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        Page {
            Label {
                text: qsTr("First page")
                anchors.centerIn: parent
            }
        }
        Page {
            Label {
                text: qsTr("Second page")
                anchors.centerIn: parent
            }
        }
    }


}
