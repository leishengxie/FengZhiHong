import QtQuick 2.0

Rectangle {
    width: 100
    height: 62

    id: root
    //width: 640
   // height: 360
    color: "#3C3C3C"

    ListModel {
    id: model
    ListElement { label:"Scientific Research";
    value:21; color:"#99e600" }
    ListElement { label:"Engineering & Design";
    value:18; color:"#99cc00" }
    ListElement { label:"Automotive";
    value:14; color:"#99b300" }
    ListElement { label:"Aerospace";
    value:13; color:"#9f991a" }
    ListElement { label:"Automation & Machine Tools";
    value:13; color:"#a48033" }
    ListElement { label:"Medical & Bioinformatics";
    value:13; color:"#a9664d" }
    ListElement { label:"Imaging & Special Effects";
    value:12; color:"#ae4d66" }
    ListElement { label:"Defense";
    value:11; color:"#b33380" }
    ListElement { label:"Test & Measurement Systems";
    value:9; color:"#a64086" }
    ListElement { label:"Oil & Gas";
    value:9; color:"#994d8d" }
    ListElement { label:"Entertainment & Broadcasting";
    value:7; color:"#8d5a93" }
    ListElement { label:"Financial";
    value:6; color:"#806699" }
    ListElement { label:"Consumer Electronics";
    value:4; color:"#8073a6" }
    ListElement { label:"Other";
    value:38; color:"#8080b3" }
    }

    Canvas {
    id: canvas
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    anchors.left: parent.left
    anchors.right: parent.horizontalCenter
    }


}

//Rectangle {
//    id: root
//    width: 360; height: 360
//    color: "#3C3C3C"
//    Canvas {
//        id: canvas
//        width: 300; height: 300
//        anchors.centerIn: parent
//        onPaint: {
//            // get the drawing context
//            var ctx = canvas.getContext(’2d’)
//            // create a rectangle path
//            ctx.rect(50, 50, 200, 200)
//            // setup fill color
//            ctx.fillStyle = "#FFF0A5"
//            // fill path
//            ctx.fill()
//            // setup line width and stroke color
//            ctx.lineWidth = 4
//            ctx.strokeStyle = "#468966"
//            // stroke path
//            ctx.stroke()
//        }
//    }
//}

