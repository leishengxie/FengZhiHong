#ifndef DAIRYEDITWIDGET_H
#define DAIRYEDITWIDGET_H

#include <QWidget>
#include <QLabel>
#include "Dairy.h"
#include "func.h"

namespace Ui {
class CDairyEditWidget;
}

class CDairyEdit;


//struct T_DragData : QObjectUserData
//{
//    int nDragType;   // 唯一标示
//    T_DragData()
//    : nDragType(0)
//    {

//    }

//   T_DragData(int nDragType)
//       : nDragType(nDragType)
//   {

//   }

//};
//Q_DECLARE_METATYPE(T_DragData)

class CDairyEditWidget : public QWidget
{
    Q_OBJECT

public:
//    enum E_DragType
//    {
//        ED_In,  // 从外部拖放到应用内部
//        ED_Out  // 从应用内部拖放到外部
//    };

    explicit CDairyEditWidget(QWidget *parent = 0);
    explicit CDairyEditWidget(T_Dairy dairy, QWidget *parent = 0);
    ~CDairyEditWidget();

    SETGETCONST(int, did, Did)

    void init();

    CDairyEdit* dairyEdit();

signals:
    void saveDairyfinished(const T_Dairy & dairySaveBefore, const T_Dairy & dairySaved);

protected:
    void closeEvent(QCloseEvent *event);//重写关闭事件
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

public slots:
    // 槽函数命名方式采用与qml一样的方式
    void onSave();
    void onCopy();

private slots:

private:
    QString getDropDownFilePath();


private:
    Ui::CDairyEditWidget *ui;

    QPoint m_ptLeftPress;
    bool m_bLeftMousePressed;
//    bool m_bHasDrag;
//    int m_nDragType;

    QLabel m_dragLabel;

};

#endif // DAIRYEDITWIDGET_H
