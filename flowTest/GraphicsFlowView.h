#ifndef CGRAPHICSFLOWVIEW_H
#define CGRAPHICSFLOWVIEW_H

#include <QGraphicsView>

class CGraphicsFlowScene;

class CGraphicsFlowView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CGraphicsFlowView(QWidget *parent = nullptr);

protected:
    // QT_CONFIG(draganddrop) 以下是选择性编译
    //void dragEnterEvent(QDragEnterEvent *event);
//    void dropEvent(QDropEvent *event);
//    void dragMoveEvent(QDragMoveEvent *event);
//    void dragLeaveEvent(QDragLeaveEvent *event);

    void wheelEvent(QWheelEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:

private:
    CGraphicsFlowScene* m_pGraphicsFlowScene;

};

#endif // CGRAPHICSFLOWVIEW_H
