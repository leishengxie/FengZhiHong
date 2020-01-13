import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.2


Rectangle {
    id: toast
    z: 100
    color: "#666666"
    opacity: bShow ? 1 : 0
    border.width: 1
    border.color: "white"
    radius: height/2
    width: 200
    height: 50
    property bool bShow: false
    property alias text: labelTip.text     // 显示的文字

    function showToast(text) {
        labelTip.text = text;
        bShow = true;
        timerToast.restart();
    }

    Label {
        id: labelTip;
        anchors.centerIn: parent
        color: "white"
    }

    Timer {
        id: timerToast
        interval: 2000
        onTriggered: toast.bShow = false
    }

    Behavior on opacity {
        NumberAnimation { duration: 1000 }
    }

}
