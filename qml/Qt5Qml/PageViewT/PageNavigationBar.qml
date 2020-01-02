import QtQuick 2.0

//import QtQuick 2.2
import QtQuick.Controls 1.2
Item
{
    id: root
    property int startPage: 1
    property int maxPage: 20
    property int selectedPage: 1
    property int totalRecord: 90
    signal pageClicked( int page )
    height: row.height
    Row
    {
        id: row
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 5
        Label{
            text:"总记录: "+totalRecord +"条";color:"white"
        }
        Label{
            text:"上一页";color:"white"
            font.underline: true
            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: {parent.color="blue";parent.x=parent.x+1;parent.y=parent.y+1}
                onExited: {parent.color="white";parent.x=parent.x-1;parent.y=parent.y-1}
                onClicked: {
                    if(startPage-1<1)
                        startPage=1
                    else
                        startPage=startPage-1
                    pageClicked(startPage)
                }
            }
        }
                Label{
                    text:"下一页";
                    color:"white"
                    font.underline: true
                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        onEntered: {parent.color="blue";parent.x=parent.x+1;parent.y=parent.y+1}
                        onExited: {parent.color="white";parent.x=parent.x-1;parent.y=parent.y-1}
                        onClicked: {
                            if(startPage+1>maxPage)
                                startPage=maxPage
                            else
                                startPage=startPage+1
                            pageClicked(startPage)
                        }
                    }
                }
                Label{
                    text:"当前页: "+"<font color='green' pointsize=14><b>"+startPage+"</b></font>";
                    color:"white"
                }
                Label{
                    text:"总页数: "+maxPage;color:"white"
                }
            }
        }

