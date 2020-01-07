import QtQuick 2.4
import lxdairy.qt.http 1.0
import QtQuick.Layouts 1.3

DairyListForm {
    anchors.fill: parent
    signal btnAddClicked();
    signal dairyEdit();

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
    //        dairyEdit();
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
    listViewDairyList.delegate: Item {
        id: delegateDiary
        x: 5
        width: listViewDairyList.width
        height: 40
        ColumnLayout {
            id: col
            Text {
                id: textTitle
                text: title
                font.bold: true
                width: 40
                height: parent.width * 0.75
                color: "red"
            }

            Text {
                id: textDataTime
                text: date
                height: parent.width * 0.25
            }

            MouseArea {
                id: mouseAreaListItem
                anchors.fill: parent
                onClicked: {
                    delegateDiary.ListView.view.currentIndex = index;
                }
            }
        }
    }
}
