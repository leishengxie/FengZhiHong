import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12


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

    //    // eg
    //    Component {
    //        id: component1
    //        Item {
    //            id: name
    //        }
    //    }
    //    property Component componentTest: component1;

    //property Component componentDairyEdit: Qt.createComponent("DairyEdit.qml");
    // componentDairyEdit为变量

    // componentDairyEdit当前已经实例化了
    property Component componentDairyEdit: DairyEdit {
        id: dairyEdit

    }

    // 使用StackView切换场景
    //
    //    SwipeView {

    //    }

    Rectangle {
        id: ahel
        property int sss: 0
    }

    StackView {
        id: stackView
        anchors.fill: parent

        initialItem: DairyList {
            //anchors.fill: parent
            onBtnAddClicked: {
                //stackView.push(Qt.resolvedUrl("DairyEdit.qml"))
                //stackView.push({item: componentDairyEdit});
                //componentDairyEdit.strTitle
                stackView.push(componentDairyEdit);
            }
            onToDairyEdit: {
                console.log("strTitle:" + strTitle);
                // 传值失败
                // componentDairyEdit貌似不是对象,或者说只有id属性，其他的全无
                //componentDairyEdit.strTitle = strTitle;
                //componentDairyEdit.strContent = strContent;
                //componentDairyEdit.initData(strTitle, strContent);
                //ahel.color

                // 传值失败
                // dairyEdit貌似还没有实例化
                //                dairyEdit.strTitle = strTitle;
                //                dairyEdit.strContent = strContent;
                //                ahel.sss = 3;
                //                stackView.push({item: componentDairyEdit});

                // 传值失败
                //stackView.push({item: componentDairyEdit, strTitle:strTitle, strContent:strContent});

                // 传值成功
                stackView.push(componentDairyEdit, {did:did, strTitle:strTitle, strContent:strContent});
                //stackView.push(componentDairyEdit, {strTitle:strTitle, strContent:strContent}, StackView.Immediate);


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
