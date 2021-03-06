import QtQuick 2.0

Item {
    id:comboBox
    property variant items: ["test0", "test1", "test2", "test3"]
    property alias selectedItem: chosenItemText.text;
    property alias selectedIndex: listView.currentIndex;
    signal comboClicked;
    width: 110;
    height: 30;
    Item { //头
        id:chosenItem
        width:parent.width;
        height:comboBox.height-1;
        Text {
            id:chosenItemText
            anchors.left: parent.left;
            anchors.margins: 3;
            anchors.verticalCenter: parent.verticalCenter

            text:comboBox.items[0];
            font.pointSize: 14;
        }
        Image { //三角
            id: imgTriangle
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            source: "images/drop.png"
        }

        MouseArea {
            anchors.fill: parent;
            onClicked: {
                comboBox.state = comboBox.state == "dropDown" ? "shrink" : "dropDown"
            }
        }
    }

    Rectangle { //下拉菜单
        id:dropDown
        width:comboBox.width;
        height:1
        clip:true;
        radius:4;
        anchors.top: chosenItem.bottom;
        anchors.topMargin: 2
        color: "lightgray"
        ListView {
            id:listView
            height:250
            width: dropDown.width-4
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: parent.top
            anchors.topMargin: 1
            z:1
            model: comboBox.items
            currentIndex: 0
            delegate: Item{
                width:listView.width;
                height: comboBox.height;
                Rectangle {
                    id: mouseMoveHighLight
                    width:listView.width;
                    height:comboBox.height;
                    color: "green";
                    opacity: 0
                    radius: 4
                    z:0
                }
                Text {
                    text: modelData
                    anchors.top: parent.top;
                    anchors.left: parent.left;
                    anchors.margins: 5;
                    font.pointSize: 14;
                    z:1
                }
                MouseArea {
                    anchors.fill: parent;
                    hoverEnabled: true
                    onClicked: {
                        comboBox.state = "shrink"
                        var preSelection = chosenItemText.text
                        chosenItemText.text = modelData
                        if(chosenItemText.text != preSelection){
                            comboBox.comboClicked();
                        }
                        listView.currentIndex = index;
                    }
                    onEntered: mouseMoveHighLight.opacity = 0.5;
                    onExited: mouseMoveHighLight.opacity = 0;
                }
            }

            highlight: Rectangle {
                width:listView.width;
                height:comboBox.height;
                color: "green";
                radius: 4
            }
        }
//        MouseArea{
//            anchors.fill: dropDown
//            hoverEnabled: true
//            onExited: {
//                if(!containsMouse)
//                    comboBox.state = "shrink";
//            }
//        }
    }
    states: [
        State {
            name: "dropDown"
            PropertyChanges {
                target: dropDown
                height: 30 * comboBox.items.length + 4
            }
        },
        State {
            name: "shrink"
            PropertyChanges {
                target: dropDown
                height: 1
            }
        }
    ]

    transitions: Transition {
        NumberAnimation {
            target: dropDown
            properties: "height"
            easing.type: Easing.OutExpo
            duration: 200
        }
    }
}

