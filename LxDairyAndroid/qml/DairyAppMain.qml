import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


// Item继承自c++ 的QQuickItem, 源文件所在路径为:
// E:\software_work\qt\qt5\5.4.0 everyWhere\qt-everywhere-opensource-src-5.4.0\qtdeclarative\src\quick\items

Item {
    id : itemMain
    anchors.fill: parent

    //    ListModel {
    //        id: pageModel
    //        ListElement {
    //            page: "DairyEdit.qml"
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

    //property Component componentDairyEdit: Qt.createComponent("DairyEdit.qml");
    property Component componentDairyEdit: DairyEdit {


    }

    // 使用StackView切换场景
    //
//    SwipeView {

//    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: DairyList {
            anchors.fill: parent
            onBtnAddClicked: {
                //stackView.push(Qt.resolvedUrl("DairyEdit.qml"))
                stackView.push({item: componentDairyEdit});
                //componentDairyEdit.strTitle
            }
            onDairyEdit: {
//                componentDairyEdit.strTitle = strTitle;
//                componentDairyEdit.strContent = strContent;
                stackView.push({item: componentDairyEdit});
//                componentDairyEdit.initData(strTitle, strContent);
            }
        }


        // modify by 20200108
        // -- example
        // end modify

        //initialItem : var

        focus: true
        Keys.onReleased: {
            if (event.key === Qt.Key_Back && stackView.depth > 1) {
                stackView.pop();
                event.accepted = true;
            }
        }


    }
}
