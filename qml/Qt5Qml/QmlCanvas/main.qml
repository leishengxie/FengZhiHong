import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

ApplicationWindow {
    title: qsTr("Hello World")
//    width: 640
//    height: 480

//    //test3
//    width: 500
//    height: 500

    //test4
    width: 800;
    height: 600
    visible: true

//    CanvasTriangle {

//    }

//    CanvasDrawRect {

//    }

    CanvasChart {

    }

//    CanvasHalfRadisBtn {

//    }

//    CanvasSpirograph {

//    }

//    //test
//    ListView{
//        id: listPage
//        width: 300
//        height: 200
//        model: changePageModel
//        default property alias content: changePageModel.children
//    //ObjectModel
//    VisualItemModel { //其中VisualItemModel 可以用ObjectModel代替
//            id: changePageModel
//            Rectangle{width: 300;height: 200;color: "green"}
//            Rectangle{width: 300;height: 200;color: "lightblue"}
//            Rectangle{width: 300;height: 200;color: "lightgreen"}
//        }
//        orientation: ListView.Horizontal
//        snapMode: ListView.SnapOneItem
//        highlightRangeMode: ListView.StrictlyEnforceRange
//        cacheBuffer: 2
//        boundsBehavior: Flickable.StopAtBounds
//    }

    //test3
//    Rectangle {
////        width: 500
////        height: 500
//        anchors.fill: parent
//        property int count: 100;
//        GridView
//        {
//            id:gridView
//            anchors.fill: parent
//            model:gridModel
//            delegate: gridDel
//            cellHeight : width/4
//            cellWidth : height/4
//            flow:Grid.TopToBottom
//            interactive: false
//            contentX: listView.contentX
//        }
//        ListView
//        {
//            id:listView
//            anchors.fill: parent
//            model: listModel
//            delegate: listDel
//            orientation: ListView.Horizontal
//            snapMode: ListView.SnapOneItem
//        }
//        Component
//        {
//            id:gridDel
//            Rectangle
//            {
//                width: gridView.width/4
//                height: gridView.height/4
//                Rectangle
//                {
//                    anchors.centerIn: parent
//                    width: gridView.width/5
//                    height: gridView.height/5
//                    border.color: "black"
//                    color:"lightblue"
//                    Text
//                    {
//                        anchors.centerIn: parent
//                        font.pixelSize: 30
//                        text:id;
//                    }
//                }
//            }
//        }
//        ListModel
//        {
//            id:gridModel
//        }
//        Component
//        {
//            id:listDel
//            Rectangle
//            {
//                width: listView.width
//                height: listView.height
//                color:"transparent"
//                border.width:3
//                border.color: "black"
//            }
//        }
//        ListModel
//        {
//            id:listModel
//        }

//        Component.onCompleted:
//        {

//            for(var i = 0;i<count;++i)
//            {
//                gridModel.append({"id":i});
//            }
//            for(var j = 0;j<count/16;++j)
//            {
//                listModel.append({});
//            }
//        }
//    }



//    //test4
//    Rectangle {
//        id: root
//anchors.fill: parent
//        Rectangle {
//            id: side
//            anchors {
//                top: parent.top
//                left: parent.left
//            }
//            width: 80
//            height: 80
//            color: "lightblue"
//            Text {
//                id: test
//                anchors.centerIn: parent
//                text: "测试"
//            }
//            MouseArea {
//                anchors.fill: parent
//                onClicked: {
//                    if (root.state == '')
//                        root.state = "minSize"
//                    else
//                        root.state = ''
//                }
//            }
//        }
//        Rectangle {
//            id: menu
//            width: 400
//            height: 100
//            color: "red"
//            anchors.left: side.right
//            anchors.top: parent.top
//            //没有这个属性com1,com2不会跟着收缩
//            //clip: true
//            Rectangle {
//                id: com1
//                width: 30
//                height: 50
//                color: "green"
//                anchors.left: parent.left
//                anchors.top: parent.top
//            }
//            Rectangle {
//                id: com2
//                width: 30
//                height: 50
//                color: "gray"
//                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.leftMargin: 30
//            }
//        }
//        states:[
//            State {
//                name: "minSize"
//                PropertyChanges {
//                    target: menu
//                    height: 10
//                }
//            }
//        ]
//        transitions: [
//           Transition {
//                NumberAnimation {
//                    target: menu
//                    property: "height";
//                    duration: 200;
//                    easing.type: Easing.InOutQuad;
//                }
//            }
//        ]
//    }
}
