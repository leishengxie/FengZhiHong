import QtQuick 2.4
import Qt.labs.settings 1.0
import lxdairy.qt.http 1.0

DairyAppLoginForm {
    anchors.fill: parent
    signal loginSucess();
    signal login();

    DairyHttpRequest {
        id: dairyHttpRequest
    }

    // ui文件不支持javascript
    btn_login.onClicked: {
        //loginSucess();
        dairyHttpRequest.login(strUserName, strPasswd, function(bSucceed) {
            console.log("c++ js callback", bSucceed);
            if (bSucceed) {
                console.log(strUserName);
                settings.bRememberUserName = checkBoxUserName.checked;
                settings.bRememberPasswd = checkBoxPasswd.checked;
                if (checkBoxUserName.checked)
                {
                    settings.strUserName = strUserName;
                }
                if (checkBoxPasswd.checked)
                {
                    settings.strPasswd = strPasswd;
                }
                loginSucess();
                return true;
            }
        })
    }

}
