import QtQuick 2.4
import lxdairy.qt.http 1.0
import QtQuick.Layouts 1.3

DairyListForm {
    anchors.fill: parent
    signal btnAddClicked();
    signal toDairyEdit(string strTitle, string strContent);

    DairyHttpRequest {
        id: dairyHttpRequest
    }

    Component.onCompleted: {
        dairyHttpRequest.dairyList();
    }

    mouseAreaAdd.onClicked: {
        btnAddClicked();
    }

    //    mouseAreaListItem.onClicked: {
    //        toDairyEdit();
    //    }

    listViewDairyList.onCurrentIndexChanged: {
        console.log("onCurrentIndexChanged");
        //listViewDairyList.currentIndex = index;
    }

    // error
    //    listViewDairyList.onSectionChanged: {
    //        console.log("onSectionChanged");
    //    }

    //    Connections {
    //        target: dairyListModel.selection
    //        onSelectionChanged: {
    //            console.log("onSectionChanged");
    //        }
    //    }

    //listViewDairyList.mo
    listViewDairyList.delegate: Rectangle {
        id: delegateDiary
        x: 5
        width: listViewDairyList.width
        height: 40
//        border.color: "green"
//        border.width: 2

        Row{
            Rectangle{//选中当前 颜色高亮
                id:curRect
                width: 5
                height: delegateDiary.height
                color: index===delegateDiary.ListView.view.currentIndex ? "lightseagreen" : "black"//选中颜色设置
            }
            ColumnLayout {
                width: delegateDiary.width - 5
                height: delegateDiary.height
                id: col
                Rectangle {
                    implicitWidth: textTitle.width
                    implicitHeight: textTitle.height
                    radius: 28;
                    color: "#81EE8E"
                    Text {
                        id: textTitle
                        text: title
                        font.bold: true
//                        width: 40
//                        height: parent.width * 0.75
                    }
                }

                Text {
                    id: textDataTime
                    text: date
//                    height: parent.width * 0.25
                    //color: ListView.isCurrentItem ? "#157efb" : "#53d769"
                }

                MouseArea {
                    id: mouseAreaListItem
                    anchors.fill: parent
                    onClicked: {
                        delegateDiary.ListView.view.currentIndex = index;
                        //toDairyEdit(title, content);
                        //                    //listViewDairyList.
                        //                    dairyListModel.curIndex = index;
                        //                    //modelData
                    }
                }

            }
        }
    }
}
