import QtQuick 2.4
import lxdairy.qt.http 1.0

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

}
