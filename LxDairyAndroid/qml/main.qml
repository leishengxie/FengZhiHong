import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
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
    Rectangle {
        id: rectMain
        anchors.fill: parent
    //property Component componentCur: null;
    property var objLogin: null;
    property var objMain: null;


    function loginSucess() {
        rectMain.objLogin.destroy();
        rectMain.objMain = Qt.createComponent("DairyAppMain.qml").createObject(rectMain);
    }

    // 搜 组件与对象动态创建详解----（Qt Quick 教程六）
    Component.onCompleted: {
        // 使用Component动态加载场景
        console.log(QmlGlobalObj.appName);
        rectMain.objLogin = Qt.createComponent("DairyAppLogin.qml").createObject(rectMain);
        rectMain.objLogin.loginSucess.connect(rectMain.loginSucess);

    }

    Component.onDestruction: {
        if (null !== rectMain.objLogin) {
            rectMain.objLogin.destroy();
        }
        if (null !== rectMain.objMain) {
            rectMain.objMain.destroy();
        }
    }
    }


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

    // 等待指示器
    //    BusyIndicator {
    //        id: busyIndicator
    //        anchors.centerIn: parent
    //        implicitWidth: 96
    //        implicitHeight: 96
    //        opacity: running ? 0.0 : 1.0
    //        //contentItem: BusyIndicator{}
    //    }

    // 繁忙指示器组件被用于指明内容被加载或UI被阻塞在等待资源可用中。
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

    Toast {
        id: toast
        anchors.centerIn: parent
    }
}
