/******************************************************************************
**
** @file
** Xg.qml
** @brief
** 机顶盒配置界面
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Controls.Styles 1.3
import com.xunge.Model 1.0

Rectangle { //主界面控件
    width: 800
    height: 600

    Rectangle { //返回上级区域
        id: rectBack
        height: 50
        width: 250
        x: 20
        y: 20
        Image { //返回-图片
            id: imgBack
            source: "images/back.png"
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
        }
        Text { //机顶盒配置-文字
            anchors.left: imgBack.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "机顶盒配置"
            font.pixelSize: 25
        }
        MouseArea { // 点击返回主页
            anchors.fill: parent
            onClicked: {
                stackView.pop();
            }
        }
    }

    Column { //左侧列
        id: col
        width: 250
        anchors.left: rectBack.left
        anchors.top: rectBack.bottom
        anchors.topMargin: 10
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20

        Rectangle { //查找
            id: rectSecah
            height: 30
            width: 250
            radius: 2
            border.color: "#7F7F7F"
            border.width: 2
            TextField {
                anchors.fill: parent
                anchors.margins: 2
                anchors.leftMargin: 12
                placeholderText: "查找机顶盒"

                style: TextFieldStyle { // 文本框背景样式定义
                    background: Rectangle {
                        radius: 2
                        border.color: "#7F7F7F"
                        border.width: 0
                    }
                }
                validator: RegExpValidator {
                    regExp: /^[0-9]*$/
                }
                function isContains(str, substr) {
                    return str.indexOf(substr) >= 0;
                }
                onTextChanged: {
//                    for (var i = 0 ; i < modelSTB.count ; ++i) {
//                        if (modelSTB.get(i).stbId.toString().indexOf(text) < 0) {
//                            modelSTB.remove(i,1);
//                            i-- ;
//                        }
//                    }

                }
                Image { //放大镜-图片
                    id: imgSheachFor
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                    anchors.verticalCenter: parent.verticalCenter
                    source: "images/seach.png"
                }
            }
        }

        Row { //全选-应用-保存
            id: rowOpreate
            height: 50
            width: 250
            TextButton { //全选按钮
                text: "全选"
                width: 120
                anchorsType: 1
                property bool isAllSelect: false
                onClicked: {
                    if (isAllSelect) {
                        modelStbName.checkAll(false)
                    }
                    else {
                       modelStbName.checkAll(true)
                    }
                    isAllSelect = !isAllSelect
                }
            }
            TextButton { //应用按钮
                text: "应用"
                width: 130
                anchorsType: 3
                onClicked: {
                    console.log("set")
                }
            }
        }


        ModelStbName {
            id: modelStbName
        }

        Component {
            id: comSTB
            Rectangle { //item项
                width: parent.width
                height: 50
                anchors.margins: 1
                color: "transparent"
                MouseArea { //鼠标区域
                    anchors.fill: parent
                    onClicked: {
                        lstSTB.currentIndex = index
                        modelStbContent.refreshModel(index)
                    }
                }
                LCheckBox { //CheckBox
                    id: chcek
                    anchors.left: parent.left
                    anchors.leftMargin: 20
                    anchors.verticalCenter: parent.verticalCenter
                    isChecked: isTempateChecked
                    onClicked: {
                        modelStbName.check(index)
                   }
                }
                Text { //No.
                    id: stbNumber
                    anchors.left: chcek.right
                    anchors.leftMargin: 20
                    anchors.bottom: parent.verticalCenter
                    anchors.bottomMargin: -2
                    font.pixelSize: 18
                    text: name
                }
                Text { //ip
                    id: stbIp
                    anchors.top: parent.verticalCenter
                    anchors.left: chcek.right
                    anchors.leftMargin: 20
                    font.pixelSize: 12
                    color: "#A3A2A2"
                    text: attachedName
                }
            }
        }
        ListView { //左侧列表
            id: lstSTB
            width: 250
            height: parent.height - rectSecah.height - rowOpreate.height
            clip: true
            focus: true
            model: modelStbName
            delegate: comSTB
            highlightMoveDuration : 200
            highlight: Item {
                z: 10
                width: lstSTB.currentItem.width
                height: lstSTB.currentItem.height
                Rectangle {
                    anchors.fill: parent
                    anchors.margins: 1
                    radius: 3
                    color: "transparent"
                    border.width: 2
                    border.color: "#7F7F7F" //Qt.lighter("#7F7F7F")
                    Behavior on border.color {
                        PropertyAnimation {
                        }
                    }
                }
            }
        }
    }

    ModelStbContent {
        id: modelStbContent
    }

    GridView { //右侧内容显示
        id: gridContent
        clip: true
        anchors.left: col.right
        anchors.leftMargin: 30
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: col.top
        anchors.bottom: col.bottom
        cellWidth: 400
        cellHeight: 45
        keyNavigationWraps: true
        model: modelStbContent
        delegate: BottomLineSelectText {
            model: modelEffect
            strName: selectName
            isHLine: !readOnly
            nCurrentIndex: curIndex
            onComboSelectChaged: {
                modelStbContent.saveCurSelect(index, nIndexChage)
            }
        }
        focus: true
    }
}

//    VisualItemModel { //itemModel
//        id: itemModel
//        BottomLineSelectText {
//            model: [803]
//            strName: "包房名称:"
//        }
//        BottomLineSelectText {
//            model: ["迅歌X1", "迅歌X2", "迅歌X3"]
//            strName: "机顶盒型号:"
//        }
//        BottomLineSelectText {
//            isHLine: false
//            model: ["F0:F6:44:A0:2F:5B"]
//            strName: "MAC地址:"
//        }
//        BottomLineSelectText {
//            model: ["铂瑞C300"]
//            strName: "触摸屏模板:"
//        }
//        BottomLineSelectText {
//            model: ["COM1", "COM2"]
//            strName: "触摸屏模板:"
//        }
//        BottomLineSelectText {
//            model: ["开启", "关闭"]
//            strName: "触摸屏定位:"
//        }
//        BottomLineSelectText {
//            model: ["默认配置", "BoRuiK-250A", "XianGe-ShiYi", "YuLeXianFeng-Light(3.5或普通)-串口V01", "CC500"]
//            strName: "中控盒模板:"
//        }
//        BottomLineSelectText {
//            model: ["COM1", "COM2"]
//            strName: "中控盒端口:"
//        }
//        BottomLineSelectText {
//            model: ["无", "DSP3140", "AIVIN M360+", "BH1207", "DK8000", "BH1209", "AIVIN K1000", "DK-3000"]
//            strName: "音效器模板:"
//        }
//        BottomLineSelectText {
//            model: ["模板1", "模板2"]
//            strName: "智能灯光模板:"
//        }
//        BottomLineSelectText {
//            model: ["是", "否"]
//            strName: "控制音效器音量:"
//        }
//        BottomLineSelectText {
//            model: ["480i", "480p", "720P 50hz", "720P 60hz",
//                "1080i 50hz", "1080i 60hz", "1080P 50hz", "1080P 60hz"]
//            strName: "TV端模式:"
//        }
//        BottomLineSelectText {
//            model: ["0"]
//            strName: "起始音量:"
//        }
//        BottomLineSelectText {
//            model: ["55"]
//            strName: "最大气氛音量:"
//        }
//        BottomLineSelectText {
//            model: ["51"]
//            strName: "最大音量:"
//        }
//        BottomLineSelectText {
//            model: ["50"]
//            strName: "TV安全区域:"
//        }
//        BottomLineSelectText {
//            model: ["显示", "关闭"]
//            strName: "云歌曲:"
//        }
//    }
