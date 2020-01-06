import QtQuick 2.0

Rectangle {

    id: container
    property string text: "Button"
    signal clicked
    width: buttonLabel.width + 20;
    height: buttonLabel.height + 5;

    border {
        width: 1;
        color: Qt.darker(sysPalette.button)
    }
    // 反锯齿
    antialiasing: true
    radius: 8
    gradient: Gradient {
        GradientStop {
            position: 0.0
            color: {
                if (mouseArea.pressed)
                    return sysPalette.dark
                else
                    return sysPalette.light
            }
        }
        GradientStop {
            position: 1.0;
            color: sysPalette.button
        }
    }
    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: container.clicked();
    }
    Text {
        id: buttonLabel
        anchors.centerIn: container
        color: sysPalette.buttonText
        text: container.text
    }
}
