/******************************************************************************
**
** @file
** MainPage.qml
** @brief
** 音效器配置入口
** @author
** wangrm
** @date
** 2017-4-18
**
******************************************************************************/
import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.3

Item { // 配置主界面

    Text { // 标题文字
        text: "迅歌VOD配置"
        font.pixelSize: 50
        anchors.top: parent.top
        anchors.topMargin: 60
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle { // 工具栏
        id: rectTool
        anchors.fill: parent
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 110
        anchors.top: parent.top
        anchors.topMargin: 170
        clip: true

        GridView { // 工具列表
            id: gridStb
            anchors.fill: parent
            cellWidth: 200
            cellHeight: 150
            keyNavigationWraps: true
            model: listModel
            delegate: contactDelegate
            focus: true
        }

        Component { // 列表属性
            id: contactDelegate

            Rectangle { // 工具单元格
                id: itemTool
                width: 140
                height: 140
                radius: 10
                color: "transparent"
                border.width: 2
                border.color: mouseItem.pressed ? "#bebebe":"#ffffff"

                Column { // 图片，文字对齐
                    anchors.fill: parent
                    spacing: 15
                    anchors.top: parent.top
                    anchors.topMargin: 20

                    Image { // 加载工具图片
                        id: imgTool
                        source: portrait
                        width: 58
                        height: 54
                        anchors.horizontalCenter: parent.horizontalCenter
                    }

                    Text { // 对应文字
                        id: textName
                        text: toolName
                        font.pixelSize: 20
                        anchors.horizontalCenter: parent.horizontalCenter

                    }
                }

                MouseArea { // 鼠标经过时
                    id: mouseItem
                    anchors.fill: parent
               //     onPressed: itemTool.border.color = "#bebebe"
               //     onReleased: itemTool.border.color = "#ffffff"

                    onClicked: {
                        if (textName.text == "机顶盒配置") {
                            stackView.push(stb);
                        } else if (textName.text == "智能灯光模板") {
                            stackView.push(lamplight);
                        } else {
                            ;
                        }
                    }
                }
            }
        }

        ListModel { // 工具栏配置
            id: listModel

            ListElement { // 机顶盒配置
                toolName: "机顶盒配置"
                portrait: "/resource/images/StbIcon.png"
            }

            ListElement { // 触摸屏模板
                toolName: "触摸屏模板"
                portrait: "/resource/images/TouchIcon.png"
            }

            ListElement { // 中控器模板
                toolName: "中控盒模板"
                portrait: "/resource/images/ControllerIcon.png"
            }

            ListElement { // 音效器模板
                toolName: "音效器模板"
                portrait: "/resource/images/EffecterIcon.png"
            }

            ListElement { // 智能灯光模板
                toolName: "智能灯光模板"
                portrait: "/resource/images/lightIcon.png"
            }

            ListElement { // 智能灯光模板
                toolName: "串口模板"
                portrait: "/resource/images/SerialIcon.png"
            }

        }
    }
}



