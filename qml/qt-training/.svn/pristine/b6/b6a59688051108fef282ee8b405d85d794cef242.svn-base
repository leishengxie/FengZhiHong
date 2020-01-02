import QtQuick 2.0

Item {
    id:　textBottomLineC
    property string text: ""
    property color  textColor: "white"

    width: 200
    height: 40
    Image {
        id: img
        anchors.bottom: parent.bottom
        source: "qrc:///line.png"
    }
    Text {
        anchors.bottom: img.top
        anchors.horizontalCenter: img.horizontalCenter
        text: textBottomLineC.text
        font.pixelSize: 20
        font.bold: true
        color: textBottomLineC.textColor
    }

}

