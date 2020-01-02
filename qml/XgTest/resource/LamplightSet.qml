/******************************************************************************
**
** @file
** LamplightSet.qml
** @brief
** 灯光模板配置
** @author
** leisx
** @date
** 2017-4-21
**
******************************************************************************/
import QtQuick 2.0
import com.xunge.Model 1.0


Item { // 灯光选择
    id: itemLamplight
    anchors.fill: parent

    function refresh(nIndex) {
         modelLamplightContent.refreshModel(nIndex)
    }

    ModelLamplightContent { //c++ model
        id: modelLamplightContent
    }

    GridView { // 灯光模式
        id: gridViewLamplightSet
        anchors.fill: parent
        cellWidth: 390
        cellHeight: 45
        model: modelLamplightContent
        delegate: BottomLineSelectText {
            model: modelLamplight
            strName: selectName
            nCurrentIndex: curIndex
            onComboSelectChaged: {
                modelLamplightContent.saveCurSelect(index, nIndexChage)
            }
        }
    }
}
