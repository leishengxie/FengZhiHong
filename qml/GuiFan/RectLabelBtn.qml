import QtQuick 2.0

Rectangle {
    id:rectBtn
    property string picSrc: ""
    property string text:""

    width:50
    height:50
    Image
    {
        id: imageBtn
        source:rectBtn.picSrc
    }
    Text
    {
        id: textLabel
        color: "#000000"
        font.pointSize: 9
        font.family: "微软雅黑"
        anchors.horizontalCenter: imageBtn.horizontalCenter
        anchors.top: imageBtn.bottom
        anchors.topMargin: 3
        text:rectBtn.text
    }
}
