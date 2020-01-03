import QtQuick 2.4
import "button"
import QtQuick.Layouts 1.3

// Rectangle继承Item
Rectangle {
    id: rectDairyList
    width: 240
    height: 400

    ColumnLayout {
        id: columnLayout1
        anchors.fill: parent
        spacing: 0

        Rectangle {
            id: rectangle3
            height: 50
            color: "#ffffff"
            Layout.fillWidth: true

            TextInput {
                id: textInput1
                width: 80
                height: 20
                text: qsTr("")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
            }
        }

        ListView {
            id: listView1
            Layout.fillHeight: true
            Layout.fillWidth: true
//            delegate: Rectangle {
//                width: stackView.width
//                height: root.height * 0.125
//                Text {
//                    id: textTitle
//                    txt
//                }
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

        Rectangle {
            id: rectangle2
            height: 50
            color: "#ffffff"
            Layout.fillWidth: true

            Rectangle {
                id: rectangle1
                width: 30
                color: "#ffffff"
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    id: textAdd
                    text: qsTr("+")
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 16
                }

                MouseArea {
                    id: mouseArea1
                    anchors.fill: parent
                    //onClicked:
                }
            }
        }


    }
}
