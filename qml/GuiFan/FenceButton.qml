import QtQuick 2.4

Rectangle{
    id:root
    width: height;
    height: 400;
    clip:true;
    color: "transparent"
    property real lineHeight: easyBorderWidth;
    property real initX: 0;

    property real  easyHeight: height*0.1;
    property real  easyBorderWidth: 1;
    property color lineColor: "#3ce8f7";

    property alias color: mainRect.color;
    property alias lineState: mainRect.state;
    property real originOffSet: lineHeight*2;

    signal clicked();

    Rectangle {
        id:mainRect;
        x:root.originOffSet;
        y:root.originOffSet;
        width: root.width - root.originOffSet*2;
        height: root.width - root.originOffSet*2;
        color: "transparent";
        //        border.width: root.easyBorderWidth;
        //        border.color: "red";
        property real initX: root.originOffSet;
        property real lineY: (height )/ 2;
        property real originValue: root.lineHeight + root.easyBorderWidth;
        property real validHeight: (height-originValue*2 - root.lineHeight)/2;

        transformOrigin: Item.TopRight;

        onXChanged: console.log("onXChanged",x)
        onYChanged: console.log("onYChanged",y)

        onStateChanged: {
            console.log("onStateChanged", state);
        }

        MouseArea{
            anchors.fill: parent;
            onClicked: {
                root.clicked();
                mouse.accepted = true;
            }
        }

        Rectangle{
            id:colorLine1;
            x:mainRect.originValue;
            y:mainRect.originValue;
            color: root.lineColor;
            width: mainRect.width - mainRect.originValue*2
            height: root.lineHeight;
        }

        Rectangle{
            id:colorLine2;
            color: root.lineColor;
            width: mainRect.width - mainRect.originValue*2
            x:mainRect.originValue;
            y:colorLine1.y + mainRect.validHeight;
            //radius: height/2;
            height: root.lineHeight;
            transformOrigin: Item.TopRight;
        }

        Rectangle{
            id:colorLine3;
            color: root.lineColor;
            width: mainRect.width - mainRect.originValue*2;
            x:mainRect.originValue;
            y:colorLine1.y + mainRect.validHeight*2;
            height: root.lineHeight;
            //radius: height/2;
            transformOrigin: Item.BottomLeft;
        }

        states: [
            State {
                name: "default"
                PropertyChanges {target: colorLine2; x:mainRect.originValue; y:colorLine1.y + mainRect.validHeight;  rotation:0}
                PropertyChanges {target: colorLine3; x:mainRect.originValue; rotation:0}
                PropertyChanges {target: mainRect; x:mainRect.initX; rotation:0}
            },
            State {
                name: "extend"
                PropertyChanges {target: colorLine2; x:mainRect.originValue - root.lineHeight; y:colorLine1.y; rotation:-45}
                PropertyChanges {target: colorLine3; x:mainRect.originValue + colorLine3.width; rotation:-90}
                PropertyChanges {target: mainRect; x:mainRect.initX - mainRect.width; rotation:-90}
            }
        ]

        transitions: [
            Transition {
                from: "default"
                to: "extend"
                SequentialAnimation{
                    ParallelAnimation{
                        PropertyAnimation{targets: [colorLine2,colorLine3]; duration: 150; properties: "x,y"}
                        RotationAnimation{targets: [colorLine2,colorLine3]; duration: 150; direction: RotationAnimation.Counterclockwise; }
                    }

                    ParallelAnimation{
                        NumberAnimation{target: mainRect;  properties: "x"; duration: 150;}
                        RotationAnimation{target: mainRect;properties: "rotation";duration: 150; direction: RotationAnimation.Counterclockwise; }
                    }
                }

            },
            Transition {
                from: "extend"
                to: "default";
                SequentialAnimation{
                    ParallelAnimation{
                        RotationAnimation{target: mainRect;properties: "rotation";duration: 150; direction: RotationAnimation.Clockwise; }
                        NumberAnimation{target: mainRect;  properties: "x"; duration: 150;}
                    }

                    ParallelAnimation{
                        PropertyAnimation{targets: [colorLine2,colorLine3]; duration: 100; properties: "x,y"}
                        RotationAnimation{targets: [colorLine2,colorLine3]; duration: 100; direction: RotationAnimation.Clockwise; }
                    }
                }
            }
        ]
    }
}

