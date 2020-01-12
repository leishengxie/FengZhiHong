pragma Singleton
import QtQuick 2.4

QtObject{
    id:data;

    property int count: 0;

    //常量
    readonly property string appName: "LxDairy";
    readonly property int value: 100;

    function printText(text){
        console.log("输出： ",text);
    }
}
