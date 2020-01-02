//import QtQuick 2.4
//import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2

import QtQuick 2.0
import QtQuick.Controls.Styles 1.2
import QtQuick.Controls 1.2

ApplicationWindow {
    title: qsTr("Hello World")
    width: 400
    height: 450
    visible: true


 //   Rectangle{
        id:root
        color:"#DD202020"
 //       anchors.fill: parent
        //数据模型
        property var jsonData1 : [
        { "firstName":"Bill" , "lastName":"Gates" },
        { "firstName":"George" , "lastName":"Bush" },
        { "firstName":"Thomas" , "lastName": "Carter" }
        ];
        property var json: [
            [
                { "title": 1, "imagePath": "author.png","des":"这是描述" },
                { "title": 2, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 3, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 4, "imagePath": "author.png","des":"这是描述" },
                { "title": 5, "imagePath": "author.png","des":"这是描述" }
            ],
            [
                { "title": 6, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 7, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 8, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 9, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 10, "imagePath": "author.png","des":"这是描述" }
            ],
            [
                { "title": 11, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 12, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 13, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 14, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 15, "imagePath": "author.png" ,"des":"这是描述"}
            ],
            [
                { "title": 16, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 17, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 18, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 19, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 20, "imagePath": "author.png" ,"des":"这是描述"}
            ],
            [
                { "title": 21, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 22, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 23, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 24, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 25, "imagePath": "author.png" ,"des":"这是描述"}
            ],
            [
                { "title": 26, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 27, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 28, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 29, "imagePath": "author.png" ,"des":"这是描述"},
                { "title": 30, "imagePath": "author.png" ,"des":"这是描述"}
            ]
        ]
        Column{
            spacing: 10
            ListModel{
                id:pmodel
                Component.onCompleted: append(json[0])
            }
            ListView{
                id:listview
                width: root.width-4
                height: root.height-30
                clip:true
                model:pmodel
                highlight:Rectangle{
                    y:listview.currentItem.y
                    color:"#604BBDE8"
                    Behavior on y{
                        SpringAnimation{duration: 300;damping: 0.2}
                    }
                }
                highlightFollowsCurrentItem:true
                highlightMoveDuration:0
                spacing:5
                delegate: Rectangle{
                    width:parent.width
                    height: 60
                    color:"transparent"
                    border.width: 1
                    border.color: "white"
                    MouseArea{
                        anchors.fill: parent
                        onClicked:listview.currentIndex=index
                    }
                    Row{
                        spacing: 5
                        width:parent.width
                        height: parent.height
                        Image{
                            width: 40
                            height: width
                            source: imagePath
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Column{
                            spacing: 5
                            anchors.verticalCenter: parent.verticalCenter
                            Text{
                                text: "<font color='green' fontSize=14><B>标题：</B></font>"+title
                                color:"gray"
                            }
                            Text{
                                text: des
                                color:"white"
                                elide: Text.ElideMiddle
                                width: listview.width-40
                            }
                        }
                    }
                }
                //列表选择显示
                ListViewIndicator{
                    target : listview
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 5
                    z: 2
                }
            }
        }
        //分页导航
        PageNavigationBar
        {
            id: pageNavigationBar
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.margins: 5
            maxPage: json.length
            totalRecord: json.length * json[0].length
            onPageClicked:
            {
                pmodel.clear( );
                pmodel.append( json[page - 1] );
            }
        }
 //   }
}
