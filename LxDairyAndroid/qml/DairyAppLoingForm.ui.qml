import QtQuick 2.0

Rectangle{

    id: login_gui
    width: 320;
    height: 480
    SystemPalette {

        id: activePalette
    }
    //背景图片
    Image    {

        id: background
        anchors {

            top: parent.top;
            bottom: parent.bottom
        }
        anchors.fill: parent
        source: "pics/pic1.png"
        fillMode: Image.PreserveAspectCrop
    }
    //顶烂
    Item    {

        id: top_bar
        width: login_gui.width;
        height: login_gui.height * 0.05
        anchors.top: login_gui.top
        Text        {

            id: title
            anchors {

                top: parent.top;
                horizontalCenter: parent.horizontalCenter
            }
            text: "登陆"
            font.bold: true
            font.pointSize: login_gui.height * 0.05 * 0.7
            color: "dark red"
        }
    }
    //空白栏
    Item    {

        id: space1
        width: login_gui.width;
        height: login_gui.height * 0.1
        anchors.top: top_bar.bottom
    }
    //登陆框
    Rectangle    {

        id: rect1
        width: login_gui.width * 0.8;
        height: login_gui.height * 0.3
        anchors {

            top: space1.bottom;
            horizontalCenter: parent.horizontalCenter
        }
        border.color: "#707070"
        color: "transparent"
        LineInput        {

            width: rect1.width * 0.8;
            height: rect1.height * 0.2
            font_size:height * 0.7
            anchors {

                horizontalCenter: rect1.horizontalCenter;
                top: rect1.top;
                topMargin: 8
            }
            hint: "请输入用户号"
        }
        LineInput        {

            width: rect1.width * 0.8;
            height: rect1.height * 0.2
            font_size:height * 0.7
            anchors {

                horizontalCenter: rect1.horizontalCenter;
                bottom: btn_login.top;
                bottomMargin: rect1.height * 0.1
            }
            hint: "请输入密码"
        }
        Button        {

            id: btn_login
            width: rect1.width * 0.35;
            height: rect1.height * 0.2
            anchors {

                left: rect1.left;
                leftMargin: 28;
                bottom: rect1.bottom;
                bottomMargin: 8
            }
            text: "登陆"
            //onClicked: SameGame.startNewGame()
        }
        Button        {

            id: btn_quit
            width: rect1.width * 0.35;
            height: rect1.height * 0.2
            anchors {

                right: rect1.right;
                rightMargin: 28;
                bottom: rect1.bottom;
                bottomMargin: 8
            }
            text: "退出"
            //onClicked: SameGame.startNewGame()
        }
    }
}
