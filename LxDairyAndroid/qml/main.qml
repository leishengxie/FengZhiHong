import QtQuick 2.5
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import lxdairy.global 1.0
import lxdairy.cpp.global 1.0
import "./global" //本方法导入单例貌似不灵, 所以又导入lxdairy.global 1.0

Window {
    id: root
    visible: true
    width: 480
    height: 800
    title: qsTr("LxDairy")
    //property Component componentCur: null;
    property var objLogin: null;
    property var objMain: null;


    function loginSucess() {
        root.objLogin.destroy();
        root.objMain = Qt.createComponent("DairyAppMain.qml").createObject(root);
    }

    // 搜 组件与对象动态创建详解----（Qt Quick 教程六）
    Component.onCompleted: {
        // 使用Component动态加载场景
        console.log(QmlGlobalObj.appName);
        root.objLogin = Qt.createComponent("DairyAppLogin.qml").createObject(root);
        root.objLogin.loginSucess.connect(root.loginSucess);

    }

    Component.onDestruction: {
        if (null != root.objLogin) {
            root.objLogin.destroy();
        }
        if (null != root.objMain) {
            root.objMain.destroy();
        }
    }

    Connections {
        target: DairyGlobalInstance
        onHttpLoading: console.log("oHttpLoading")
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

}
