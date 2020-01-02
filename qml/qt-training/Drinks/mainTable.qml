import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.2
import leisx.qt.ModelMander 1.0

ApplicationWindow {
    title: "Hello World"
    width: Screen.width
    height: Screen.height
    color: "#261562"
    visible: true

    ModelMander {
        id: modelMander
    }

    TabWidget {
        id: tabTitle
        width: parent.width * 0.25
        height: parent.height * 0.6
        x: parent.width * 0.05
        y: parent.height / 2 - height / 2
        Rectangle {
            property string title: "酒水类别"
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            ListView {
                id: lstDrinksClass
                anchors.fill: parent
                model: drinksNameModel
                delegate: TextBottomLineC {
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

            Row {
                anchors.bottomMargin: 20
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                RectLabelBtn { // "上一页"
                    picSrc: "images/cashier/prev2.png"
                }

                Text {
                    text: ""
                }

                RectLabelBtn { //text: "下一页"
                    picSrc: "images/cashier/next2.png"
                }
            }
        }

        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "消费情况"
            Column {
                anchors.fill: parent
                spacing: 2
                TextBottomLine {
                    id: roomType
                    text: "房型:"
                }
                TextBottomLine {
                    id: dataTime
                    text: "开房时间:"
                }
                TextBottomLine {
                    id: roomRate
                    text: "房费:"
                }
                TextBottomLine {
                    id: miniCharge
                    text: "最低消费:"
                }
                TextBottomLine {
                    id: waitConsumptionCharge
                    text: "待消费金额:"
                }
                TextBottomLine {
                    id: freeOfCharge
                    text: "赠品金额:"
                }
                TextBottomLine {
                    id: discountCharge
                    text: "折扣金额:"
                }
                TextBottomLine {
                    id: staffOperator
                    text: "操作员:"
                }
                TextBottomLine {
                    id: vip
                    text: "会员:"
                }
            }


        }
    }

    TabWidget {
        id: tabContent
        width: parent.width * 0.6
        height: parent.height * 0.6
        anchors.left: tabTitle.right
        anchors.leftMargin: 20
        anchors.top: tabTitle.top
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "点取酒水"

            //            TableView {
            //                backgroundVisible : false
            //                id: tableDrinks
            //                anchors.fill: parent
            //                frameVisible: false
            //                sortIndicatorVisible: true
            //                //horizontalScrollBarPolicy: Qt.ScrollBarAlwaysOff
            //                //verticalScrollBarPolicy: Qt.ScrollBarAlwaysOff

            //                //                contentFooter: Rectangle {
            //                //                    color: "#419AF1"
            //                //                }
            //                //                contentHeader:Rectangle {
            //                //                    color: "#419AF1"
            //                //                }
            //                headerDelegate: Rectangle {
            //                    height: tableDrinks.height / 8
            //                    color: "#419AF1"
            //                    border.width: 1
            //                    border.color: "white"
            //                }

            //                itemDelegate: Rectangle {
            //                    height: tableDrinks.height / 8
            //                    color: "#419AF1"
            //                    border.width: 1
            //                    border.color: "white"
            //                    Text {
            //                        anchors.verticalCenter: parent.verticalCenter
            //                        color: styleData.textColor
            //                        elide: styleData.elideMode
            //                        text: styleData.value
            //                    }
            //                }
            //                //                rowDelegate:Rectangle {
            //                //                    width: 200
            //                //                    height: 50
            //                //                    color:"#90000000"
            //                //                    Text{
            //                //                        text: styleData.alternate
            //                //                        anchors.centerIn: parent
            //                //                    }
            //                //                    Rectangle{
            //                //                        anchors.bottom: parent.bottom;height: 1;width: parent.width
            //                //                        color:"red"
            //                //                    }
            //                //                }

            //                TableViewColumn {
            //                    role: "index";
            //                    title: "序号";
            //                    width: tableDrinks.width / 8
            //                    //                    delegate: Rectangle{
            //                    //                        color:"#60FF0000" //"red"
            //                    //                        Text{
            //                    //                            anchors.centerIn: parent
            //                    //                            text: styleData.value
            //                    //                        }
            //                    //                    }
            //                }
            //                TableViewColumn {
            //                    role: "goldName";
            //                    title: "商品名称";
            //                    width: tableDrinks.width * 3 / 8
            //                    //                    delegate: Rectangle{
            //                    //                        color:"#60FF0000" //"red"
            //                    //                        Text{
            //                    //                            anchors.centerIn: parent
            //                    //                            text: styleData.value
            //                    //                        }
            //                    //                    }
            //                }
            //                TableViewColumn {
            //                    role: "num";
            //                    title: "数量";
            //                    width: tableDrinks.width / 8
            //                }
            //                TableViewColumn {
            //                    role: "unitPrice";
            //                    title: "单价";
            //                    width: tableDrinks.width / 8
            //                }
            //                TableViewColumn {
            //                    role: "figure";
            //                    title: "金额";
            //                    width: tableDrinks.width / 8
            //                }
            //                TableViewColumn {
            //                    role: "remark";
            //                    title: "备注";
            //                    width: tableDrinks.width / 8
            //                }

            Row {
                id: rowTitle
                width: parent.width
                height: 50
                z: 1
                anchors.top: parent.top
                RectBorder {
                    width: parent.width / 8
                    height: parent.height
                    text: "序号"
                }
                RectBorder {
                    width: parent.width * 3 / 8
                    height: parent.height
                    text: "商品名称"
                }
                RectBorder {
                    width: parent.width / 8
                    height: parent.height
                    text: "数量"
                }
                RectBorder {
                    width: parent.width / 8
                    height: parent.height
                    text: "单价"
                }
                RectBorder {
                    width: parent.width / 8
                    height: parent.height
                    text: "金额"
                }
                RectBorder {
                    width: parent.width / 8
                    height: parent.height
                    text: "备注"
                }
            }

            ListView {
                //anchors.fill: parent
                id: lstGoods
                anchors.top: rowTitle.bottom
                anchors.bottom: toolGroup.top
                anchors.bottomMargin: 20
                width: parent.width
                //clip: false
                // ffd                                                   dragging: false
                //moving : false
                //boundsBehavior: ListView.DragAndOvershootBounds
                //boundsBehavior: ListView.DragOverBounds
                model: drinksModel
                //                model: ListModel {
                //                    ListElement {
                //                        index: "序号"
                //                        goldName:"商品名称"
                //                        num: "数量"
                //                        unitPrice: "单价"
                //                        figure: "金额"
                //                        remark: "备注"

                delegate: comRow
                Component {
                    id: comRow
                    Item {
                        id: delegateItem
                        width: parent.width
                        //height: parent.height
                        height: 50

                        Row {
                            //width: parent.width
                            //spacing: 0.5
                            anchors.fill: parent
                            RectBorder {
                                width: parent.width / 8
                                height: parent.height
                                text: index
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            RectBorder {
                                width: parent.width * 3 / 8
                                height: parent.height
                                text: goldName
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            RectBorder {
                                width: parent.width / 8
                                height: parent.height
                                text: num
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            RectBorder {
                                width: parent.width / 8
                                height: parent.height
                                text: unitPrice
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            RectBorder {
                                width: parent.width / 8
                                height: parent.height
                                text: figure
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                            RectBorder {
                                width: parent.width / 8
                                height: parent.height
                                text: remark
                                textColor: delegateItem.ListView.isCurrentItem ? "red" : "white"
                            }
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: delegateItem.ListView.view.currentIndex = index

                        }
                    }
                }
            }

            RowBtnGroup {
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
                z: 1
                //anchors.horizontalCenter: parent.horizontalCenter

                RectLabelBtn {
                    picSrc: "images/cashier/prev2.png"
                }

                RectLabelBtn {
                    picSrc: "images/cashier/next2.png"
                }

            }
        }
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "点单明细"
        }
        Rectangle {
            anchors.fill: parent
            radius: 10
            color: "#419AF1"
            property string title: "消费明细"

        }
    }

}
