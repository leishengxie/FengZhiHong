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

CDairyEdit::CDairyEdit(QWidget *parent)
    : QTextEdit(parent)
{

}

CDairyEdit::CDairyEdit(CDairy dairy, QWidget *parent)
: QTextEdit(parent)
{

}



void CDairyEdit::init()
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(current_file_path_ + "[*]");
}





bool CDairyEdit::save()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);//设置整个应用程序的光标形状为等待形状，因为如果文件的内容非常多时可以提醒用户
    setPlainText(in.readAll());//读取文本流中的所有内容，并显示在其窗体中
    QApplication::restoreOverrideCursor();//恢复开始时的光标状态

    if(is_saved_)//已经保存过至少一次后，则说明文件的文件名等已经弄好了，直接保存内容即可。
        return SaveFile(current_file_path_);
    else return SaveAs();//第一次保存时，需要调用SaveAs
}



bool CDairyEdit::SaveFile(const QString &file_name)
{

    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();//以纯文本方式写入，核心函数
    QApplication::restoreOverrideCursor();

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

//顶层窗口被关闭时发出的事件
void CDairyEdit::closeEvent(QCloseEvent *event)
{
    if(document()->isModified())
        event->accept();
    else
        event->ignore();

}

