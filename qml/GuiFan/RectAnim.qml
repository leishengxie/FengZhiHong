
import QtQuick 2.3

Rectangle {
    width: 100
    height: 62

    Rectangle{
        id:animltion
        y:40
        width: 40
        height: 40
        NumberAnimation on x{
            to:40+Math.random()*(parent.width-40);duration: 3000
            //loops: Animation.loops
        }
    }
    Rectangle{
        id:animltion2
        y:80
        width: 40
        height: 40
        RotationAnimation on rotation{

            to:360;duration: 3000;
            loops:Animation.Infinite
        }
    }

    Rectangle{
        id:animltion3
        y:120
        width: 40
        height: 40
        NumberAnimation on opacity{
            to:0;duration: 3000
        }
    }
    Rectangle{
        id:animltion4
        y:160
        width: 40
        height: 40
        ScaleAnimator on scale{
            from:0.5;to:1;duration: 3000
        }
    }
    //Behavior on
    Rectangle{
        id:animltion5
        y:200
        x:0
        width: 40
        height: 40
        //signal clicked()
        Behavior on x{
            NumberAnimation {duration: 3000}
        }
        //onClicked: x=90
        MouseArea{
            anchors.fill: parent
            onClicked:parent.x=400
        }
    }
    //standalone
    Rectangle{
        id:animltion6
        y:240
        width: 40
        height: 40

        NumberAnimation{
            id:anim6
            target: animltion6
            properties: "x"
            from:400
            to:40
            duration: 3000
        }
        MouseArea{
            anchors.fill: parent
            onClicked: anim6.start()
        }
    }
}

