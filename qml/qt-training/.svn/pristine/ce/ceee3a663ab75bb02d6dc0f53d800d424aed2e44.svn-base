/******************************************************************************
**
** @file
** main.qml
** @brief
** 主界面显示
** @author
** leisx
** @date
** 2017-4-12
**
******************************************************************************/
import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.2
import leisx.qt.ModelMander 1.0

ApplicationWindow { //主控件
    title: "Hello World"
    width: Screen.width
    height: Screen.height
    color: "#261562"
    visible: true

    property int goodsIndex: 0

    ModelMander { //c++ model
        id: modelMander
    }


    CustomTab { //酒水选单
        id: tabTitle
        width: parent.width * 0.25
        height: parent.height * 0.6
        x: parent.width * 0.05
        y: parent.height / 2 - height / 2
        Rectangle { //tab项
            property string title: "酒水类别"
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            ListView { //酒水选单名称列表
                id: lstDrinksClass
                anchors.top: parent.top
                anchors.bottom: rowCtrl.top
                anchors.bottomMargin: 20
                width: parent.width
                model: drinksNameModel
                clip: true
                property int nPostionIndex: 0
                property int nPageItemCount: 8

                function prevPage() {
                    if (nPostionIndex >= nPageItemCount) {
                        nPostionIndex -= nPageItemCount;
                    }
                    positionViewAtIndex(nPostionIndex,ListView.Beginning);
                    //currentIndex = nPostionIndex
                }

                function nextPage() {
                    onClicked: {
                        if (nPostionIndex <= lstGoods.count - nPageItemCount) {
                            nPostionIndex += nPageItemCount;
                        }
                        positionViewAtIndex(nPostionIndex,ListView.Beginning);
                        //currentIndex = nPostionIndex
                    }
                }

                delegate: BottomLine2Text { //项名称
                    id: wrapper
                    height: 50
                    width: parent.width
                    text: modelData
                    textColor: ListView.isCurrentItem ? "#F5EB1C" : "white"
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            wrapper.ListView.view.currentIndex = index
                            modelMander.onDrinksC(index)

                        }
                    }
                }
            }

            Row { //翻页控制
                id: rowCtrl
                anchors.bottomMargin: 20
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                HalfRadisButton { // "上一页"
                    text: "上一页"
                    onClicked: lstDrinksClass.prevPage()
                }

                Item {
                    id: name
                    height: 50
                    width: 50
                    Text {
                        anchors.centerIn: parent
                        color: "white"
                        font.pixelSize: 20
                        text: parseInt(lstDrinksClass.nPostionIndex / 8 + 1) + "/" + parseInt(lstDrinksClass.count / 8 + 1)
                    }
                }
                HalfRadisButton { //text: "下一页"
                    text: "下一页"
                    isRight: false
                    onClicked: lstDrinksClass.nextPage()
                }
            }
        }

        Rectangle { //消费详细
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "消费情况"
            Column {
                anchors.fill: parent
                spacing: 2
                BottomLineText {
                    id: roomType
                    text: "房型:"
                }
                BottomLineText {
                    id: dataTime
                    text: "开房时间:"
                }
                BottomLineText {
                    id: roomRate
                    text: "房费:"
                }
                BottomLineText {
                    id: miniCharge
                    text: "最低消费:"
                }
                BottomLineText {
                    id: waitConsumptionCharge
                    text: "待消费金额:"
                }
                BottomLineText {
                    id: freeOfCharge
                    text: "赠品金额:"
                }
                BottomLineText {
                    id: discountCharge
                    text: "折扣金额:"
                }
                BottomLineText {
                    id: staffOperator
                    text: "操作员:"
                }
                BottomLineText {
                    id: vip
                    text: "会员:"
                }
            }
        }
    }

    CustomTab { //酒水内容tab
        id: tabContent
        width: parent.width * 0.6
        height: parent.height * 0.6
        anchors.left: tabTitle.right
        anchors.leftMargin: 20
        anchors.top: tabTitle.top
        titleWidth: 200
        isShareItem: true
        Rectangle { //点取酒水项
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "点取酒水"
            Column {
                id: columnTitle
                z: 1
                width: parent.width
                height: 50
                anchors.top: parent.top
                Row {
                    width: parent.width
                    height: parent.height - 1
                    //spacing: 1
                    BorderButton {
                        width: parent.width / 8 - 1
                        height: parent.height
                        text: "序号"
                    }
                    VLine {

                    }
                    BorderButton {
                        width: parent.width * 3 / 8 - 1
                        height: parent.height
                        text: "商品名称"
                    }
                    VLine {

                    }
                    BorderButton {
                        width: parent.width / 8 - 1
                        height: parent.height
                        text: "数量"
                    }
                    VLine {

                    }
                    BorderButton {
                        width: parent.width / 8 - 1
                        height: parent.height
                        text: "单价"
                    }
                    VLine {

                    }
                    BorderButton {
                        width: parent.width / 8 - 1
                        height: parent.height
                        text: "金额"
                    }
                    VLine {

                    }
                    BorderButton {
                        width: parent.width / 8 - 1
                        height: parent.height
                        text: "备注"
                    }
                }
                HLine {
                    id: lineTitle
                }
            }

            RadioBtnGroup {
                id: toolGroup
                height: 50
                width: 630
                anchors.bottomMargin: 20
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.leftMargin: 10
                z: 1

            }

            Row {
                anchors.bottomMargin: 20
                anchors.bottom: parent.bottom
                anchors.left: toolGroup.right
                anchors.leftMargin: 20
                spacing: 10
                z: 1
                //anchors.horizontalCenter: parent.horizontalCenter

                HalfRadisButton {
                    text: "上一页"
                    //onClicked: lstGoods.positionViewAtBeginning();
                    onClicked: {
                        if (goodsIndex >= 7) {
                            goodsIndex -= 7;
                        }
                        lstGoods.positionViewAtIndex(goodsIndex,ListView.Beginning);
                    }
                }

                HalfRadisButton {
                    text: "下一页"
                    isRight: false
                    onClicked: {
                        if (goodsIndex <= lstGoods.count - 7) {
                            goodsIndex += 7;
                        }
                        lstGoods.positionViewAtIndex(goodsIndex,ListView.Beginning);
                    }
                }

            }



            ListView { //酒水内容列表
                //anchors.fill: parent


                id: lstGoods
                anchors.top: columnTitle.bottom
                anchors.bottom: toolGroup.top
                anchors.bottomMargin: 20
                width: parent.width
                //orientation: ListView.Horizontal
                clip: true
                //dragging: false
                //moving : false
                //boundsBehavior: ListView.DragAndOvershootBounds
                //boundsBehavior: ListView.DragOverBounds
                //displayMarginBeginning: 0
                //visibleArea.xPosition: 0
                model: drinksModel
                delegate: comRow
                Component {
                    id: comRow
                    Item {
                        id: delegateItem
                        width: parent.width
                        //height: parent.height
                        height: 50
                        //color: "white"
                        Row {
                            //width: parent.width
                            //spacing: 1
                            id: rowItem
                            anchors.fill: parent
                            BorderButton {
                                width: parent.width / 8 - 1
                                height: parent.height
                                text: index + 1
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            VLine {

                            }
                            BorderButton {
                                width: parent.width * 3 / 8 - 1
                                height: parent.height
                                text: goldName
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            VLine {

                            }
                            BorderButton {
                                width: parent.width / 8 - 1
                                height: parent.height
                                text: num
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            VLine {

                            }
                            BorderButton {
                                width: parent.width / 8 - 1
                                height: parent.height
                                text: unitPrice
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            VLine {

                            }
                            BorderButton {
                                width: parent.width / 8 - 1
                                height: parent.height
                                text: figure
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            VLine {

                            }
                            BorderButton {
                                width: parent.width / 8 - 1
                                height: parent.height
                                text: remark
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                        }
                        HLine {
                            anchors.bottom: parent.bottom
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: delegateItem.ListView.view.currentIndex = index

                        }
                    }
                }
            }


        }
        Rectangle { //点单明细项
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "点单明细"
        }
        Rectangle { //消费明细项
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "消费明细"

        }
    }

}
