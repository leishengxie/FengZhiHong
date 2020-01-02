/******************************************************************************
**
** @file
** LamplightGeneral.qml
** @brief
** 属性设置页面
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.2

Item { // 设备属性

    VisualItemModel { //itemModel
        id: itemModel

        BottomLineSelectText { // 模板名称
            model: ["默认配置"]
            strName: "模板名称:"
            width: 390
        }

        BottomLineSelectText { // 串口模板
            model: ["默认配置", "串口配置1", "串口配置2", "串口配置3"]
            strName: "串口模板:"
             width: 390

            Label { // 串口信息
                font.pixelSize: 15
                color: "gray"
                anchors.top: parent.bottom
                anchors.topMargin: -3
                anchors.left: parent.left
                anchors.leftMargin: 40
                text: "波特率：115200，数据位：8，停止位：1，校验：无"
            }
        }
    }

    GridView { //右侧内容显示
        id: gridContent
        anchors.fill: parent
        clip: true
        cellWidth: 390
        cellHeight: 65
        keyNavigationWraps: true
        model: itemModel
        focus: true
    }

}




