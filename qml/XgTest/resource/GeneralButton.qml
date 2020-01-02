import QtQuick 2.0

Rectangle {
    id: rectGeneral
    width: 107
    height: 42
    border.color: "#0078d7"
    border.width: 1
    radius: 10

    property alias text: textCancel.text
    property color pressedColor: "#0078d7"
    property color releasedColor: "white"
    signal clicked
    Text {
        id: textCancel
        anchors.centerIn: parent
        font.pixelSize: 20
        color: "#0078d7"
    }
        MouseArea {
            hoverEnabled: true
            anchors.fill: parent
            onPressed: {
                rectGeneral.state = 'pressed'
            }
            onReleased: {
                rectGeneral.state = 'released'
                rectGeneral.clicked()
            }
        }

        states:
        [
            State {
                name: "pressed"
                PropertyChanges { target: rectGeneral; color: pressedColor }
                PropertyChanges { target: textCancel; color: releasedColor }
            },

            State {
                name: "released"
                PropertyChanges { target: rectGeneral; color: releasedColor }
                PropertyChanges { target: textCancel; color: pressedColor }
            }
        ]
    }
