import QtQuick 2.0

Rectangle {
    id: rectBorder
    width: 100
    height: 62
//    BorderImage {
//        id: name
//        source: "file"
//        width: 100; height: 100
//        border.left: 5; border.top: 5
//        border.right: 5; border.bottom: 5
//    }

    //border.color: "white"
    //border.width: 1
    color: "#419AF1"

    property string text: ""
    property color textColor: "white"

    Text {
        id: name
        anchors.centerIn: parent
        text: rectBorder.text
        color: rectBorder.textColor
        font.pixelSize: 20
        font.bold: true
    }
}


