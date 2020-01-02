import QtQuick 2.0

Rectangle {

    id:root
    width: 100
    height: 62

    anchors.fill: parent
    PathView{
        anchors.fill:parent
        delegate:flipCardDelegate
        model:100
        path:Path{
            startX:root.width/2  //链接路径
            startY:0
            PathAttribute{name:"itemZ";value:0}
            PathAttribute{name:"itemAngle";value:-90.0;}
            PathAttribute{name:"itemScale";value:0.5;}
            PathLine{x:root.width/2;y:root.height*0.4;}  //使用二维数组来构造路径
            PathPercent{value:0.48;}                      //按比例播放
            PathLine{x:root.width/2;y:root.height*0.5;}
            PathAttribute{name:"itemAngle";value:0.0;}
            PathAttribute{name:"itemScale";value:1.0;}
            PathAttribute{name:"itemZ";value:100}
            PathLine{x:root.width/2;y:root.height*0.6;}
            PathPercent{value:0.52;}
            PathLine{x:root.width/2;y:root.height;}
            PathAttribute{name:"itemAngle";value:90.0;}
            PathAttribute{name:"itemScale";value:0.5;}
            PathAttribute{name:"itemZ";value:0}
        }
        pathItemCount:16             //显示项数
        preferredHighlightBegin:0.5 //高亮区间
        preferredHighlightEnd:0.5
    }
    Component{
        id:flipCardDelegate
        Item{
            id:wrapper
            width:64
            height:64
            visible:PathView.onPath
            scale:PathView.itemScale
            z:PathView.itemZ
            property variant rotX:PathView.itemAngle
            transform:Rotation{axis{x:1;y:0;z:0}
                angle:wrapper.rotX
                origin{
                    x:32
                }
            }
            Rectangle {
                anchors.fill:parent
                color:"lightGray"
                border.color:"black"
                border.width:3
            }
            Text{
                anchors.centerIn:parent
                text:index
                font.pixelSize:30

            }
        }
    }
}

