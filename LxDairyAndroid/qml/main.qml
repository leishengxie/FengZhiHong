import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Window {
    id: root
    visible: true
    width: 480
    height: 800
    title: qsTr("LxDairy")

//    ListModel {
//        id: pageModel
//        ListElement {
//            page: "content/ButtonPage.qml"
//        }
//        ListElement {
//            page: "content/SliderPage.qml"
//        }
//    }

//    property var componentMap: {
//        "CircularGauge": circularGauge,
//                "DelayButton": delayButton,
//                "Dial": dial,
//                "Gauge": gauge,
//                "PieMenu": pieMenu,
//                "StatusIndicator": statusIndicator,
//                "ToggleButton": toggleButton,
//                "Tumbler": tumbler
//    }
    StackView {
        id: stackView
        anchors.fill: parent

        DairyList {

            anchors.fill: parent
        }

        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                             stackView.pop();
                             event.accepted = true;
                         }


    }

}
