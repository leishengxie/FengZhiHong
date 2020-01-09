import QtQuick 2.0

// 创建焦点范围。他继承与Item, 因此拥有Item拥有的一切属性。
FocusScope {
    id: focusScope
    property alias text: textInput.text
    property alias placeholderText: textplaceholder.text
    property int font_size: 12
    property alias echoMode: textInput.echoMode
    signal accepted
    width: 200
    height: 30

    Rectangle {
        anchors.fill: parent
        border.color: "green"
        radius: 4

        TextInput {
            id: textInput
            focus: true
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            color: "black"
            font.pixelSize: font_size
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
