#include "DairyEdit.h"
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QApplication>
#include <QFileInfo>
#include <QFileDialog>
#include <QPushButton>
#include <QCloseEvent>
#include <QMenu>
#include <QtDebug>

CDairyEdit::CDairyEdit(QWidget *parent)
    : QTextEdit(parent)
{

}

CDairyEdit::CDairyEdit(const QString &text, QWidget *parent)
    : QTextEdit(text, parent)
{

}





void CDairyEdit::contextMenuEvent(QContextMenuEvent *event)
{
//    QMenu *menu = new QMenu;

//    //QKeySequence类是专门封装快捷键的，这里使用的是默认的快捷键操作，其快捷键位"&"号后面那个字母
//    QAction *undo = menu->addAction(tr("撤销(&U)"), this, SLOT(undo()), QKeySequence::Undo);//直接调用槽函数undo()
//    undo->setEnabled(document()->isUndoAvailable());//因为该类是一个widget，所以可以直接使用document()函数

//    QAction *redo = menu->addAction(tr("恢复(&A)"), this, SLOT(redo()), QKeySequence::Redo);
//    redo->setEnabled(document()->isRedoAvailable());

//    menu->addSeparator();//增加分隔符

//    QAction *cut = menu->addAction(tr("剪切(&T)"), this, SLOT(cut()), QKeySequence::Cut);
//    cut->setEnabled(textCursor().hasSelection());

//    QAction *copy = menu->addAction(tr("复制(&C)"), this, SLOT(copy()), QKeySequence::Copy);
//    copy->setEnabled(textCursor().hasSelection());

//    menu -> addAction(tr("粘贴&P"), this, SLOT(paste()), QKeySequence::Paste);

//    QAction *clear = menu->addAction(tr("清空"), this, SLOT(clear()));
//    clear->setEnabled(!document()->isEmpty());//文本内容非空时就可以清除

//    menu->addSeparator();//增加分隔符

//    QAction *select_all = menu->addAction(tr("全选"), this, SLOT(selectAll()), QKeySequence::SelectAll);
//    select_all->setEnabled(!document()->isEmpty());

//    menu->exec(event->globalPos());//获取鼠标位置，并显示菜单

//    delete menu;//销毁这个菜单
}

//上层窗口被关闭时发出的事件
void CDairyEdit::closeEvent(QCloseEvent *event)
{
    qDebug() << this->parent();
    event->accept();
}

