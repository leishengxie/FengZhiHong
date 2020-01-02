import QtQuick 2.0

Item {
    id:　textBottomLine
    property string text: ""

    width: 200
    height: 40
    Image {
        id: img
        anchors.bottom: parent.bottom
        source: "qrc:///line.png"
    }
    Text {
        anchors.bottom: img.top
        x: 20
        text: textBottomLine.text
        font.pixelSize: 20
        font.bold: true
        color: "white"
    }

}



