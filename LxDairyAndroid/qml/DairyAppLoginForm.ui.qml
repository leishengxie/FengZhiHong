import QtQuick 2.0
import QtQuick.Layouts 1.3

Rectangle {
    id: login_gui
    width: 240
    height: 400
    property alias btn_login: btn_login
    property alias btn_quit: btn_quit
    property alias strUserName: lineInputUser.text
    property alias strPasswd: lineInputPasswd.text

    ColumnLayout {
        id: column1
        anchors.fill: parent
        SystemPalette {
            id: sysPalette
        }
        //背景图片
        //    Image    {
        //        id: background
        //        anchors {

        //            top: parent.top;
        //            bottom: parent.bottom
        //        }
        //        anchors.fill: parent
        //        source: "pics/pic1.png"
        //        fillMode: Image.PreserveAspectCrop
        //    }
        //顶烂


        Text {
            id: title
            text: "登陆"
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            font.bold: true
            font.pointSize: login_gui.height * 0.05 * 0.7
            color: "dark red"
        }




        LineInput {
            id: lineInputUser
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBottom
            font_size:height * 0.7
            placeholderText: "请输入用户号"
        }
        LineInput {
            id: lineInputPasswd
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            font_size:height * 0.7
            placeholderText: "请输入密码"
        }

//        TextInput {
//            text: "请输入用户号"
//        }
//        TextInput {
//            text: "请输入密码"
        //            font.pointSize: 9
        //        }

        Row {
            spacing: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            GradientButton {
                id: btn_login
                text: "登陆"
            }
            GradientButton {
                id: btn_quit
                text: "退出"
            }
        }
    }

}
