import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12
import lxdairy.global 1.0
import lxdairy.cpp.global 1.0
import "./global" //本方法导入单例貌似不灵, 所以又导入lxdairy.global 1.0
import "./tip"

Window {
    id: root
    visible: true
    width: 480
    height: 800
    title: qsTr("LxDairy")

    // 主界面显示区域
    Rectangle {
        id: rectCenter
        anchors.fill: parent
        //property Component componentCur: null;
        property var objLogin: null;
        property var objMain: null;


        function loginSucess() {
            rectCenter.objLogin.destroy();
            rectCenter.objMain = Qt.createComponent("DairyAppMain.qml").createObject(rectCenter);
        }

        // 搜 组件与对象动态创建详解----（Qt Quick 教程六）
        Component.onCompleted: {
            // 使用Component动态加载场景
            console.log(QmlGlobalObj.appName);
            rectCenter.objLogin = Qt.createComponent("DairyAppLogin.qml").createObject(rectCenter);
            rectCenter.objLogin.loginSucess.connect(rectCenter.loginSucess);

        }

        Component.onDestruction: {
            if (null !== rectCenter.objLogin) {
                rectCenter.objLogin.destroy();
            }
            if (null !== rectCenter.objMain) {
                rectCenter.objMain.destroy();
            }
        }
    }



    // qml自带的
    BusyIndicator {
        id:busyIndicator
        z:4
        running: false
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height/3.
        /*
        Timer{
            interval: 2000
            running: busyIndicator.running
            onTriggered: {
                busyIndicator.running = false
            }
        }
        */

    }

    //
    Toast {
        id: toast
        anchors.centerIn: parent
    }


    /*
      相关函数
      */
    Connections {
        target: DairyGlobalInstance
        onHttpLoading: {
            busyIndicator.running = true
            console.log("oHttpLoading")
        }
        onHttpLoadingFinished: {
            busyIndicator.running = false
        }
        onToast: {
            //console.log(strTip)
            toast.showToast(strTip)
        }
    }


    // -qmljsdebugger=port:26666
}
