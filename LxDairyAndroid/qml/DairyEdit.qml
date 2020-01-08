import QtQuick 2.4
import lxdairy.qt.http 1.0

// M300错误去除红色下划线-----缩进{
DairyEditForm {
    anchors.fill: parent
    //signal btnUploadClicked();

    DairyHttpRequest {
        id: dairyHttpRequest
    }

    mouseAreaUpload.onClicked: {
        //btnUploadClicked();
        dairyHttpRequest.uploadDairy(strTitle, strContent);
    }

    function initData(title, content) {
        strTitle = title;
        strContent = content;
    }

    Component.onCompleted: {
        //dairyListModel.data()
    }

}
