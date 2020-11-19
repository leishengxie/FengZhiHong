import QtQuick 2.4

TestUiForm {
    //property alias text: textTest.text

    textTest.text: "12345"

    Component.objectName: {
        textTest.text = "6789"
    }

    textTest.mouseArea.onClicked: {

    }

}
