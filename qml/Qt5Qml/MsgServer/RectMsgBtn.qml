import QtQuick 2.0

Rectangle {

    id:rectMsgBtn

        property string text:""

        signal clicked

    width: 27
    height: 22
    color:"#00000000"
    //border { left: 10; top: 10; right: 10; bottom: 10 }
    //border.width: 10
    radius:10

    MouseArea {
//        hoverEnabled: true
        anchors.fill: parent
//        onEntered: sysbtn.state == "pressed" ? sysbtn.state = "pressed" : sysbtn.state = "hover"
//        onExited: sysbtn.state == "pressed" ? sysbtn.state = "pressed" : sysbtn.state = "normal"
//        onPressed: sysbtn.state = "pressed"
        onReleased:
        {
            //rectMsgBtn.state = "normal"
            rectMsgBtn.clicked()
        }
    }

    Text
    {
        id: textLabel
        color: "#000000"
        font.pointSize: 12
        font.family: "微软雅黑"
        anchors.centerIn: parent
        text:rectMsgBtn.text
    }
}

