/******************************************************************************
**
** @file
** LamplightPage.qml
** @brief
** 灯光配置页
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0
import com.xunge.Model 1.0

Item { //主界面控件
    width: 800
    height: 600
    id: boxTemplate

    property int nLastIndex: 0
    property string templateParameterSymbol: "通用属性"   // 模板参数显示页面page标记
    property string dlgFileName: ""

    function pageGain() { // 参数判断,确定加载显示哪个页面
        if (boxTemplate.templateParameterSymbol == "通用属性") {
            return "LamplightGeneral.qml"
        }
        else if (boxTemplate.templateParameterSymbol == "智能灯光") {
            return "LamplightSet.qml"
        }
    }

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
        Text { //智能灯光模板-文字
            anchors.left: imgBack.right
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            text: "智能灯光模板"
            font.pixelSize: 25
        }
        MouseArea { // 点击返回主页
            anchors.fill: parent
            onClicked: {
                modelLamplightName.requireSet()
                stackView.pop();
            }
        }
    }

    Row { //添加-删除
        id: rowOperate
        anchors.top: rectBack.bottom
        height: 50
        width: 250
        TextButton { //添加按钮
            text: "添加"
            width: 120
            anchorsType: 1
            property bool isAllSelect: false
            onClicked: {
            console.log("add")
                dlgFileName = "DlgAdd.qml";
                loaderDlgAdd.item.strTitle = "创建模板"
            }
        }
        TextButton { //删除按钮
            text: "删除"
            width: 130
            anchorsType: 3
            onClicked: {
                modelLamplightName.deleteTemplate(nLastIndex)
                listLamplight.currentIndex = 0
                nLastIndex = 0
                if (boxTemplate.templateParameterSymbol == "智能灯光") {
                    loaderPage.item.refresh(0)
                }
            }
        }
    }


    ModelLamplightName { //c++ model
        id: modelLamplightName

    }

    ListView { //灯光模板名称列表
        id: listLamplight
        model: modelLamplightName
        width: 250
        clip: true
        anchors.top: rowOperate.bottom
        anchors.topMargin: 20
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.bottom: parent.bottom
        highlightFollowsCurrentItem: true
        highlightMoveDuration: 200

        highlight: Rectangle { // 点击列表效果
            height: 50
            width: 250
            border.color: "#7f7f7f"
            border.width: 2
            color: "#ffffff"
            radius: 3
        }

        delegate: Rectangle { // 点击列表变色
            id: wrapperLanguage
            height: 50
            width: 250
            color: "transparent"
            clip: true

            Text { // 定义列表内容
                id: contactInfoLanguage
                font.pixelSize: 20
                text: tempName
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.top: parent.top
                anchors.topMargin: 15
            }

            MouseArea { // 点击效果
                anchors.fill: parent
                onClicked: {
                    wrapperLanguage.ListView.view.currentIndex = index // 点击变色
                    nLastIndex = index
                    if (boxTemplate.templateParameterSymbol == "智能灯光") {
                        loaderPage.item.refresh(index)
                    }
                }
            }
        }
    }


    Rectangle { // 通用属性
        id: buttonBoxTemplateGeneral
        anchors.top: rectBack.bottom
        anchors.left: rowOperate.right
        anchors.leftMargin: 20
        radius: 5
        width: 90
        height: 30
        color: "#ffffff"
        border.color: "#ffffff"

        Text { // 按键标签"通用属性"
            id: textProperties
            text: "通用属性"
            color: "blue"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        MouseArea { // 点击效果
            anchors.fill: parent
            onContainsMouseChanged: buttonBoxTemplateGeneral.state == 'clicked' ? buttonBoxTemplateGeneral.state = "" : buttonBoxTemplateGeneral.state = 'clicked'
            onClicked: {
                boxTemplate.templateParameterSymbol = "通用属性";
            }
        }

        states: [ // 设置点击效果
            State {　// 设置点击效果
                name: "clicked"
                PropertyChanges { // 点击变灰色
                    target: buttonBoxTemplateGeneral
                    border.color: "#f0f0f0"
                }
            }
        ]
        Rectangle { // 下划线
            height: 2
            width: 77
            color: "blue"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            visible: boxTemplate.templateParameterSymbol == "通用属性"
            x: 7
        }
    }

    Rectangle { // 智能灯光
        id: rectSound
       // x: parent.width > 800 ? ((parent.width - 300)/4) + 300 : 400
        anchors.left: buttonBoxTemplateGeneral.right
        anchors.top: rectBack.bottom
        radius: 5
        width: 90
        height: 30
        color: "#ffffff"
        border.color: "#ffffff"

        Text { // 按键标签"智能灯光"
            id: textSound
            text: "智能灯光"
            color: "blue"
            font.pixelSize: 20
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            onContainsMouseChanged: rectSound.state == 'clicked' ? rectSound.state = "" : rectSound.state = 'clicked'
            onClicked: {
                boxTemplate.templateParameterSymbol = "智能灯光";
                loaderPage.item.refresh(nLastIndex)
            }
        }

        states: [ // 设置点击效果
            State {　// 设置点击效果
                name: "clicked"

                PropertyChanges { // 点击变灰色
                    target: rectSound
                    border.color: "#f0f0f0"
                }
            }
        ]

        Rectangle { // 下划线
            height: 2
            width: 88
            color: "blue"
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            visible: boxTemplate.templateParameterSymbol == "智能灯光"
            x: 4
        }
    }

    Loader { // 切换界面
        id: loaderPage
        anchors.top: rowOperate.bottom
        anchors.left: buttonBoxTemplateGeneral.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        source: boxTemplate.pageGain()
    }

    Loader {
        id: loaderDlgAdd
        anchors.centerIn: parent
        source: dlgFileName
    }

    Connections {
            target: loaderDlgAdd.item
            onSaveTemplateName: {
                modelLamplightName.addTemplate(strName)
            }
        }
}
