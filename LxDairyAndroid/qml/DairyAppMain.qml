import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4

Item {
    id : itemMain
    anchors.fill: parent

    ListModel {
        id: pageModel
        ListElement {
            page: "DairyEdit.qml"
        }
    }

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


    // 使用StackView切换场景
    StackView {
        id: stackView
        anchors.fill: parent

        DairyList {
            anchors.fill: parent
        }

        //initialItem : var

        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                             stackView.pop();
                             event.accepted = true;
                         }


    }
}
