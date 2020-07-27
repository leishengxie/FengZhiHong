import QtQuick 2.4
import QtGraphicalEffects 1.0

// 等待指示器
//    BusyIndicator {
//        id: busyIndicator
//        anchors.centerIn: parent
//        implicitWidth: 96
//        implicitHeight: 96
//        opacity: running ? 0.0 : 1.0
//        //contentItem: BusyIndicator{}
//    }

// 繁忙指示器组件被用于指明内容被加载或UI被阻塞在等待资源可用中。
Item {
    property alias running: rotationAnimation.running
    Rectangle {
        id: rect
        width: parent.width
        height: parent.height
        color: Qt.rgba(0, 0, 0, 0)
        radius: width / 2
        border.width: width / 6
        visible: false
    }

    ConicalGradient {
        width: rect.width
        height: rect.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: "#80c342" }
            GradientStop { position: 1.0; color: "#006325" }
        }
        source: rect

        Rectangle {
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: rect.border.width
            height: width
            radius: width / 2
            color: "#006325"
        }

        RotationAnimation on rotation {
            from: 0
            to: 360
            duration: 800
            loops: Animation.Infinite
        }
    }
}
