import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import QtQuick.Particles 2.0
import "./button"
import "./com_input"

Rectangle {
    id: login_gui
    width: 240
    height: 400
    property alias lineInputPasswd: lineInputPasswd
    property alias btn_login: btn_login
    property alias btn_quit: btn_quit
    property alias strUserName: lineInputUser.text
    property alias strPasswd: lineInputPasswd.text
    property alias settings: settings
    property alias checkBoxUserName: checkBoxUserName
    property alias checkBoxPasswd: checkBoxPasswd


    Settings {
        id: settings
        property bool bRememberUserName: false
        property bool bRememberPasswd: false
        property string strUserName: ""
        property string strPasswd: ""
    }

    Item {

        anchors.fill: parent
        ParticleSystem {
            id: particleSystem
        }

        Emitter {
            id: emitter
            anchors.fill: parent
            system: particleSystem
            emitRate: 10
            lifeSpan: 2000
            lifeSpanVariation: 500
            size: 16
            endSize: 32
        }

        ImageParticle {
            system: particleSystem
            source: "qrc:/img/leaf.png"
            //color: "#FFD700"
            //colorVariation: 0.6
            rotation: 15
            rotationVariation: 5
            rotationVelocity: 45
            rotationVelocityVariation: 15
            entryEffect: ImageParticle.Scale
        }
    }

    // :/img/leaf.png
    ColumnLayout {
        id: column1
        anchors.fill: parent

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



        Column {
            spacing: 10
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
            LineInput {
                id: lineInputUser
                font_size:height * 0.7
                placeholderText: "请输入用户号"
                text: settings.strUserName
            }
            LineInput {
                id: lineInputPasswd
                font_size:height * 0.7
                placeholderText: "请输入密码"
                text: settings.strPasswd
                echoMode: TextInput.Password
            }

//            TextInput {
//                id: lineInputUser
//            }
//            TextInput {
//                id: lineInputPasswd
//            }


            Row {
                spacing: 10
                CheckBox {
                    id: checkBoxUserName
                    text: "记住账号"
                    checked: settings.bRememberUserName
                }
                CheckBox {
                    id: checkBoxPasswd
                    text: "记住密码"
                    checked: settings.bRememberPasswd
                }
            }
        }

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
