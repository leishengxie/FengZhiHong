import QtQuick 2.4

FocusScope {
    id: focusScope
    property alias text: textInput.text
    property alias placeholderText: textplaceholder.text
    property alias font: textInput.font
    property alias echoMode: textInput.echoMode
    signal accepted
    width: 200
    height: 30

    Rectangle {
        anchors.fill: parent
        border.color: "green"
        radius: 4

        TextInput {
            // 草拟吗什么时候加的Z
            //id: textInputZ
            id: textInput
            focus: true
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            color: "black"
            onAccepted: focusScope.accepted()
        }

        // PlaceholderText 占位文本
        Text {
            id: textplaceholder
            anchors {
                fill: parent;
                leftMargin: 2
            }
            verticalAlignment: Text.AlignVCenter
            color: "#707070"
            opacity: textInput.length ? 0 : 1
        }

    }
}
