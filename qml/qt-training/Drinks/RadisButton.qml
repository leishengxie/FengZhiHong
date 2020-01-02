/******************************************************************************
**
** @file
** RadisButton.qml
** @brief
** 圆弧类button
** @author
** leisx
** @date
** 2017-4-12
**
******************************************************************************/
import QtQuick 2.0

Rectangle {
    id: toolbtn
    height: 50
    width: 100
    border.color: "white"
    border.width: 1
    radius: 20
    //gradient: on
    //property alias picSrc: pic.source
    property alias btnText: label.text
    property int index:0
    signal clicked(int btnIndex)
    property color bkColor: "#77AFE6"

//    Gradient
//    {
//        id:on
//        GradientStop { position: 0.0; color: "#00FFFFFF" }
//        GradientStop { position: 1.0; color: bkColor }
//    }

//    Image
//    {
//        id:pic
//        anchors.topMargin: 5
//        anchors.horizontalCenter: parent.horizontalCenter
//    }

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
        onEntered:toolbtn.state == 'checked' ? toolbtn.state = 'checked' : toolbtn.state = 'hover'
        onExited:toolbtn.state == 'checked' ? toolbtn.state = 'checked' : toolbtn.state = 'leave'
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
                bkColor:"#E4666F"
            }
        },

        State {
            name: "hover"
            PropertyChanges {
                target: toolbtn
                bkColor:"#77FFFF"
            }
        },

        State {
            name: "leave"
            PropertyChanges {
                target: toolbtn
                bkColor:"#77AFE6"
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

