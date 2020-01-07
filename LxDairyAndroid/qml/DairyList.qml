import QtQuick 2.4
import lxdairy.qt.http 1.0

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
    }
    listViewDairyList.onSectionChanged: {
        console.log("onSectionChanged");
    }
}
