import QtQuick 2.4
import lxdairy.qt.http 1.0

    DairyAppLoginForm {
        anchors.fill: parent
        signal loginSucess
        signal login


        // ui文件不支持javascript
        btn_login.onClicked: {
            //loginSucess();
            dairyHttpRequest.login(strUserName, strPasswd, function(bSucceed) {
                console.log("c++ js callback", bSucceed);
//                if (bSucceed != true) {
                    loginSucess();
//                    return true;
//                }
            })
        }

        DairyHttpRequest {
            id: dairyHttpRequest
        }
}
