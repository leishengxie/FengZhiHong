import QtQuick 2.0

Rectangle
{
    id:textBtn

    property string picCurrent: ""
    property string picNormal: ""
    property string picHover: ""
    property string picPressed: ""

    signal clicked

    width: 27
    height: 22
    color:"#00000000"
    state:"normal"

    Image
    {
        source: picCurrent;
    }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onEntered: textBtn.state == "pressed" ? textBtn.state = "pressed" : textBtn.state = "hover"
        onExited: textBtn.state == "pressed" ? textBtn.state = "pressed" : textBtn.state = "normal"
        onPressed: textBtn.state = "pressed"
        onReleased:
        {
            textBtn.state = "normal"
            textBtn.clicked()
        }
    }

    states:
    [
        State{
            name:"hover"
            PropertyChanges {
                target: textBtn
                picCurrent:picHover
            }
        },
        State {
            name: "normal"
            PropertyChanges {
                target: textBtn
                picCurrent:picNormal
            }
        },
        State {
            name: "pressed"
            PropertyChanges {
                target: textBtn
                picCurrent:picPressed
            }
        }

    ]
}
