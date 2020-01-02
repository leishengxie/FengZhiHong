import QtQuick 2.0

Rectangle {
    id: radisBtnBg

    property alias text: textLabel.text
    property bool isRight: true
    signal clicked

    radius: 20
    height: 50
    width: 80
    antialiasing: true;//抗锯齿，默认就是开启的
    clip: true //这一属性设置表示如果他的子类超出了范围，那么就剪切掉，不让他显示和起作用
//    onIsRightChanged: {
//        isRight ? rectHalfBtn.x = x : rectHalfBtn.x = x - 20
//    }

    Rectangle {

        id:rectHalfBtn
        height: 50
        width: 100
        border.color: "white"
        border.width: 1
        radius: 20
        color: "#77AFE6"
        x: isRight ? parent.x : -20

        MouseArea
        {
            hoverEnabled: true
            anchors.fill: parent
            onPressed:
            {
                rectHalfBtn.state = 'pressed'
            }
            onReleased:
            {
                rectHalfBtn.state = 'released'
                radisBtnBg.clicked()
            }
        }

        states:
        [
            State {
                name: "pressed"
                PropertyChanges { target: rectHalfBtn; color: "#E4666F" }
            },

            State {
                name: "released"
                PropertyChanges { target: rectHalfBtn; color: "#77AFE6" }
            }
        ]
    }

    Text
    {
        id: textLabel
        color: "white"
        font.pixelSize: 20
        anchors.centerIn: parent
    }

    Rectangle {
        height: parent.height
        width: 1
        color: "white"
        x: isRight ? parent.x + parent.width - 1 : 0
    }
}


//Canvas{

//    width: 400;
//    height: 240;
//    contextType: "2d";
//    onPaint: {

//        context.lineWidth = 2;
//        context.strokeStyle = "red";
//        context.fillStyle = "blue";
//        context.beginPath();
//        context.moveTo(100 ,80);
//        context.lineTo(100 , 200);
//        context.lineTo(300 ,200);
//        context.closePath();
//        //context.fill();
//        context.stroke();

//    }
//}

