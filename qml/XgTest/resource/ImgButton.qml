import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3

Rectangle {
    id:rectImgBtn
    property string picSrc: ""
    property string text:""

    signal clicked

    width:100
    height:50

    Image
    {
        anchors.fill: parent
        id: imageBtn
        source:rectImgBtn.picSrc
    }

//    Text
//    {
//        id: textLabel
//        color: "#000000"
//        font.pixelSize: 20
//        font.bold: true
//        anchors.horizontalCenter: imageBtn.horizontalCenter
//        anchors.top: imageBtn.bottom
//        anchors.topMargin: 3
//        text:rectImgBtn.text
//    }

    MouseArea
    {
        hoverEnabled: true
        anchors.fill: parent
        onPressed:
        {
            rectImgBtn.state = 'pressed'
        }
        onReleased:
        {
            rectImgBtn.state = 'released'
            rectImgBtn.clicked()
        }
    }

    states:
    [
        State {
            name: "pressed"
            PropertyChanges { target: rectImgBtn; scale: 1.1 }
        },

        State {
            name: "released"
            PropertyChanges { target: rectImgBtn; scale: 1.0 }
        }
    ]
}

//Button {
//    id:btn
//    property string picSrc: ""
//    //property string text:""

//    width:100
//    height:50

////    style: ButtonStyle{
////        background: Rectangle{
////            implicitWidth: 80
////            implicitHeight: 60
////            border.width: control.press ? 4 : 2
////            border.color: (control.hovered || control.pressed) ? "blue" : "green"
////        }
////    }

//   iconName: picSrc

//}
