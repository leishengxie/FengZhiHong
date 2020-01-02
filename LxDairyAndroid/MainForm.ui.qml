import QtQuick 2.5

Rectangle {
    id: rectangle1

    width: 300
    height: 480

    ListView {
        id: listView1
        x: 125
        y: 100
        width: 110
        height: 160
        delegate: Item {
            x: 5
            width: 80
            height: 40
            Row {
                id: row1
                spacing: 10
                Rectangle {
                    width: 40
                    height: 40
                    color: colorCode
                }

                Text {
                    text: name
                    font.bold: true
                    anchors.verticalCenter: parent.verticalCenter
                }
            }
        }
        model: ListModel {
            ListElement {
                name: "Grey"
                colorCode: "grey"
            }

            ListElement {
                name: "Red"
                colorCode: "red"
            }

            ListElement {
                name: "Blue"
                colorCode: "blue"
            }

            ListElement {
                name: "Green"
                colorCode: "green"
            }
        }
    }

    RedButton {
        id: redButton1
        x: 113
        y: 318
        opacity: 0
    }
    states: [
        State {
            name: "State1"

            PropertyChanges {
                target: redButton1
                opacity: 1
            }
        }
    ]
}
