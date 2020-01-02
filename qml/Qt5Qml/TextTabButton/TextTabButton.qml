import QtQuick 2.0
import QtQuick.Controls 2.0

Rectangle {
    property alias img:image.source ;
    property alias txt:label.text ;

    height: parent.height
    width: height
    color: tabBar.color
    property int index: 0;

    Image {
        height: parent.height * 0.8
        width: height
        id:image
        anchors.left: parent.left
        MouseArea{
            id:mouseArea
            anchors.fill: parent
            onPressed: {
                console.log("pressed:"+parent.parent.index);
                swipeView.currentIndex=index;
            }
        }
    }
    Label{
        id:label
        anchors.top: image.bottom
        anchors.topMargin: 3
        anchors.horizontalCenter: image.horizontalCenter
    }

    states: [
        State {
            name: "default";
            when: mouseArea.pressed == false;
            PropertyChanges {target: image; opacity:1.0}
            PropertyChanges {target: label; font.bold: false}
        },
        State {
            name: "pressed";
            when: mouseArea.pressed == true;
            PropertyChanges {target: image; opacity:0.4}
            PropertyChanges {target: label; font.bold: true}
            //PropertyChanges {target: swipeView; currentIndex: index}
        }
    ]
}

