import QtQuick 2.0
import QtQuick.Controls 1.1
import an.qt.ColorMaker 1.0

Rectangle {
    width: 360;
    height: 360;

    Text {
        id: timeLabel;
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.top: parent.top;
        anchors.topMargin: 4;
        font.pixelSize: 26;
    }
    ColorMaker {
        id: colorMaker;
        color: Qt.green;
    }

    Rectangle {
        id: colorRect;
        anchors.centerIn: parent;
        width: 200;
        height: 200;
        color:"blue";
    }

    Button {
        id: start;
        text: "start";
        anchors.left: parent.left;
        anchors.leftMargin: 4;
        anchors.bottom: parent.bottom;
        anchors.bottomMargin: 4;
        onClicked: {
            colorMaker.start();
        }
    }
    Button {
        id: stop;
        text: "stop";
        anchors.left: start.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            colorMaker.stop();
        }
    }

    function changeAlgorithm(button, algorithm){
        switch(algorithm)
        {
        case 0:
            button.text = "RandomRGB";
            break;
        case 1:
            button.text = "RandomRed";
            break;
        case 2:
            button.text = "RandomGreen";
            break;
        case 3:
            button.text = "RandomBlue";
            break;
        case 4:
            button.text = "LinearIncrease";
            break;
        }
    }

    Button {
        id: colorAlgorithm;
        text: "RandomRGB";
        anchors.left: stop.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;

        property var curAlgorithm: colorMaker.algorithm
        onClicked: {
//            var algorithm = (colorMaker.algorithm() + 1) % 5;
//            console.log("algorithm is %d",algorithm);
//            changeAlgorithm(colorAlgorithm, algorithm);
//            colorMaker.setAlgorithm(algorithm);
            colorMaker.nextAlgorithm();
        }

        onCurAlgorithmChanged: {
            changeAlgorithm(colorAlgorithm, curAlgorithm);
        }
    }

    Button {
        id: quit;
        text: "quit";
        anchors.left: colorAlgorithm.right;
        anchors.leftMargin: 4;
        anchors.bottom: start.bottom;
        onClicked: {
            Qt.quit();
        }
    }

    Component.onCompleted: {
        colorMaker.color = Qt.rgba(0,180,120, 255);   //这个地方直接调用了c++库中的setcolor函数，是因为Q_PROPERTY定义了属性color的写函数调用对象
        colorMaker.setAlgorithm(ColorMaker.LinearIncrease);
        changeAlgorithm(colorAlgorithm, colorMaker.algorithm());
    }

    Connections {
        target: colorMaker;
        onCurrentTime:{
            timeLabel.text = strTime;
            timeLabel.color = colorMaker.timeColor;
            console.log("colorMaker.timeColor is ",colorMaker.timeColor);
        }
    }

    Connections {
        target: colorMaker;
        onColorChanged:{
            colorRect.color = color;
             console.log("Color is ",color);
        }
    }
}
