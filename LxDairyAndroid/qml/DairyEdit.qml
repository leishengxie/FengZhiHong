import QtQuick 2.4
import lxdairy.qt.http 1.0
import lxdairy.qt.model 1.0

// M300错误去除红色下划线-----缩进{
DairyEditForm {
    anchors.fill: parent
    //signal btnUploadClicked();
//    property string m_strTitle: ""
//    property string m_strContent: ""

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

    function init() {
        var a;
    }

    Component.onCompleted: {
//        map.insert("did", tDairy.did);
//        map.insert("title", tDairy.strTitle);
//        map.insert("date", tDairy.strDateTime);
//        map.insert("content", tDairy.strContent);
//        var dairy = dairyListModel.dataCurRow();
//        strTitle = dairy["title"];
//        strContent = dairy["content"];
    }

}
