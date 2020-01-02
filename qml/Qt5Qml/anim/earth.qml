import QtQuick 2.0

Rectangle {
    Column{
        spacing: 2
        Repeater{
            model:ListModel{
                ListElement{name:"Mercury";surfaceColor:"gray"}
                ListElement{name:"Venus";surfaceColor:"yellow"}
                ListElement{name:"Earth";surfaceColor:"blue"}
                ListElement{name:"Mars";surfaceColor:"orange"}
                ListElement{name:"Jupiter";surfaceColor:"orange"}
                ListElement{name:"Saturn";surfaceColor:"yellow"}
                ListElement{name:"Uranus";surfaceColor:"lightBlue"}
                ListElement{name:"Neptune";surfaceColor:"lightBlue"}
            }
            Rectangle{
                width:100
                height:20
                radius:3
                color:"lightBlue"
                Text{
                    anchors.centerIn:parent
                    text:name
                }
                Rectangle{
                    anchors.left:parent.left
                    anchors.verticalCenter:parent.verticalCenter
                    anchors.leftMargin:2
                    width:16
                    height:16
                    radius:8
                    border.color:"black"
                    border.width:1
                    color:surfaceColor
                }
            }
        }
    }
}

