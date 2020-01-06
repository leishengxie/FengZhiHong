import QtQuick 2.0

// 创建焦点范围。他继承与Item, 因此拥有Item拥有的一切属性。
FocusScope {
    id: focusScope
    property alias text: textInput.text
    property alias placeholderText: textplaceholder.text
    property int font_size: 18
    signal accepted
    width: 200
    height: 30

    Rectangle {
        anchors.fill: parent
        border.color: "#707070"
        color: "#c1c1c1"
        radius: 4

        TextInput {
            id: textInput
            focus: true
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.pixelSize:00
            color: "black"
            onAccepted: focusScope.accepted()
        }

        // PlaceholderText 占位文本
        Text {
            id: textplaceholder
            anchors {
                fill: parent;
                leftMargin: 14
            }
            verticalAlignment: Text.AlignVCenter
            text: "Enter word"
            font.pixelSize: font_size
            color: "#707070"
            opacity: textInput.length ? 0 : 1
        }



    }
}
