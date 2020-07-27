import QtQuick 2.12
import lxdairy.qt.http 1.0
import lxdairy.qt.model 1.0

// M300错误去除红色下划线-----1、缩进{再去掉缩进(偶尔灵) 2、ctrl+A, ctrl+I

DairyEditForm {
    anchors.fill: parent
    //signal btnUploadClicked();
    //    property string m_strTitle: ""
    //    property string m_strContent: ""

//    DairyHttpRequest {
//        id: dairyHttpRequest
//    }

//    mouseAreaUpload.onClicked: {
//        //btnUploadClicked();
//        dairyHttpRequest.uploadDairy(did, strTitle, strContent);
//    }

//    mouseAreaBack.onClicked: {
//        // 直接使用stackView的id
//        stackView.pop()
//    }

//    function initData(title, content) {
//        strTitle = title;
//        strContent = content;
//    }

//    function init() {
//        var a;
//    }

//    function ensureVisible(r)
//    {
//        if (flick.contentX >= r.x)
//            flick.contentX = r.x;
//        else if (flick.contentX+flick.width <= r.x+r.width)
//            flick.contentX = r.x+r.width-flick.width;
//        if (flick.contentY >= r.y)
//            flick.contentY = r.y;
//        else if (flick.contentY+flick.height <= r.y+r.height)
//            flick.contentY = r.y+r.height-flick.height;
//    }

//    textEditContent.onCursorRectangleChanged: {
//        ensureVisible(textEditContent.cursorRectangle)
//    }

//    Component.onCompleted: {
//        //        map.insert("did", tDairy.did);
//        //        map.insert("title", tDairy.strTitle);
//        //        map.insert("date", tDairy.strDateTime);
//        //        map.insert("content", tDairy.strContent);
//        //        var dairy = dairyListModel.dataCurRow();
//        //        strTitle = dairy["title"];
//        //        strContent = dairy["content"];
//    }

}
