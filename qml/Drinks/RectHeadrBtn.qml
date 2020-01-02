import QtQuick 2.0

Rectangle {
    id: rectHeaderBtn
    height: 50
    width: 100
    border.color: "white"
    border.width: 1
    radius: 20

    property alias btnText: label.text
    property int index:0
    signal clicked(int btnIndex)
    property color bkColor: "#77AFE6"

    color: bkColor

    Text
    {
        id: label
        color: "#ffffff"
        font.pixelSize: 20
        font.bold: true
        anchors.centerIn: parent
     }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onPressed:
        {
            toolbtn.state = 'checked'
            toolbtn.clicked(toolbtn.index)
        }
    }

    states: [
        State {
            name: "checked"
            PropertyChanges {
                target: toolbtn
                bkColor:"#6196FC"
            }
        },

        State {
            name: "leave"
            PropertyChanges {
                target: toolbtn
                bkColor:"#395FAA"
            }
        }
    ]

    transitions: [
        Transition {
            PropertyAnimation {
                property:"bkColor"
                easing.type: Easing.Linear
                duration: 200
            }
        }
    ]
}


