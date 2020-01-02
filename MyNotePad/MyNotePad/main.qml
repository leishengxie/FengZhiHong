import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import FileDialog 1.0


ApplicationWindow {
    title: qsTr("MyNotepad")
    width: 960
    height: 600
    visible: true

    Rectangle {
        id: screen
        anchors.fill: parent
        state: "DRAWER_CLOSED"

        property int partition: height / 3
        MyMenuBar {
            id: menuBar
            height: screen.partition
            width: screen.width
            z: 1
        }

        MyTextArea {
            id: textArea
            y: drawer.height
            color: "#3F3F3F"
            fontColor: "#DCDCCC"
            height: screen.partition * 2
            width: parent.width
        }

        Rectangle {
            id: drawer
            height:15; width: parent.width
            border.color : "#6A6D6A"
            border.width: 1
            z: 1

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#8C8F8C" }
                GradientStop { position: 0.17; color: "#6A6D6A" }
                GradientStop { position: 0.77; color: "#3F3F3F" }
                GradientStop { position: 1.0; color: "#6A6D6A" }
            }

            Image {
                id: arrowIcon
                source: "images/arrow.png"
                anchors.horizontalCenter: parent.horizontalCenter

                Behavior { NumberAnimation { property: "rotation"; easing.type: Easing.OutExpo } }
            }

            MouseArea {
                id: drawerMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onEntered: parent.border.color = Qt.lighter("#6A6D6A")
                onExited: parent.border.color = "#6A6D6A"
                onClicked: {
                    if (screen.state == "DRAWER_CLOSED")
                        screen.state = "DRAWER_OPEN"
                    else if (screen.state == "DRAWER_OPEN")
                        screen.state = "DRAWER_CLOSED"
                }
            }
        }

        //! [states]
        states: [
            State {
                name: "DRAWER_OPEN"
                PropertyChanges { target: menuBar; y: 0 }
                PropertyChanges { target: textArea; y: screen.partition + drawer.height }
                PropertyChanges { target: drawer; y: screen.partition }
                PropertyChanges { target: arrowIcon; rotation: 180 }
            },
            State {
                name: "DRAWER_CLOSED"
                PropertyChanges { target: menuBar; y: -height; }
                PropertyChanges { target: textArea; y: drawer.height; height: screen.height - drawer.height }
                PropertyChanges { target: drawer; y: 0 }
                PropertyChanges { target: arrowIcon; rotation: 0 }
            }
        ]
        //! [states]

        //! [transitions]
        transitions: [
            Transition {
                to: "*"
                NumberAnimation { target: textArea; properties: "y, height"; duration: 100; easing.type: Easing.OutExpo }
                NumberAnimation { target: menuBar; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
                NumberAnimation { target: drawer; properties: "y"; duration: 100; easing.type: Easing.OutExpo }
            }
        ]
        //! [transitions]
    }


}
