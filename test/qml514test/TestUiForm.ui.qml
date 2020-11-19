import QtQuick 2.4

Item {
    width: 400
    height: 400

    property alias textTest: textTest

    Text {
        id: textTest
        text: "hello"
        anchors.centerIn: parent
        property alias mouseArea: mouseArea

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }

}
