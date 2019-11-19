#include "InductiveBookWidget.h"
#include "ui_InductiveBookWidget.h"
#include <QListView>
#include "OcrHandleWidget.h"

CInductiveBookWidget::CInductiveBookWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CInductiveBookWidget)
    , m_pOcrHandleWidget(new COcrHandleWidget)
{
    ui->setupUi(this);
    //QListView

    ui->checkButton->setText("标记归纳文本");
    connect(ui->checkButton, SIGNAL(clicked(bool)), this, SLOT(bold(bool)));
    connect(ui->btnOcr, SIGNAL(clicked()), m_pOcrHandleWidget, SLOT(show()));
    connect(ui->listView, SIGNAL(btnAddClicked()), this, SLOT(addInductiveArticle()));
}

CInductiveBookWidget::~CInductiveBookWidget()
{
    m_pOcrHandleWidget->deleteLater();
    delete ui;
}

void CInductiveBookWidget::addInductiveArticle()
{
    //QTextCharFormat
}

void CInductiveBookWidget::mergeFormat(QTextCharFormat fmt)
{
    QTextCursor cursor = ui->textEdit->textCursor();
    if (!cursor.hasSelection())
    {
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
}

void CInductiveBookWidget::bold(bool bBold)
{
    QTextCharFormat fmt;
    //fmt.setFontItalic(bBold); 斜体
    if (bBold)
    {

        fmt.setFontWeight(QFont::Bold);
        fmt.setForeground(QColor(100, 184, 255));
    }
    else
    {
        fmt.setFontWeight(QFont::Normal);
        fmt.setForeground(Qt::black);
    }
    mergeFormat(fmt);

}


//3. 如何遍历QTextEdit中的内容

//　　QTextEdit中的内容实际上是由QTextDocument维护

//　　可以简单的理解: QTextDocument 包含 N个QTexBlock(段落), 每个QTexBlock包含N个QTextFragment

QColor _GetRamdomColor()
{
    QColor col;
    int RamdomNum = rand() % 0xffffff;
    char strCol[8];
    sprintf(strCol, "#%06x", RamdomNum);
    col.setNamedColor(QString::fromLocal8Bit(strCol, 8));
    return col;
}


void MyClass::OnTest()
{
    QTextDocument *document = ui.textEdit->document();
    QTextBlock &currentBlock = document->begin();
    QTextBlock::iterator it;
    QTextCursor cursor = ui.textEdit->textCursor();

    while( true)
    {
        // 在修改chatformat时会改变当前Block的fragment
        // 所以++it的处理类似std::map中的erase操作
        for (it = currentBlock.begin(); !(it.atEnd()); )
        {
            QTextFragment currentFragment = it.fragment();
            QTextImageFormat newImageFormat = currentFragment.charFormat().toImageFormat();

            if (newImageFormat.isValid()) {
                // 判断出这个fragment为image
                ++it;
                continue;
            }


            if (currentFragment.isValid())
            {
                ++it;
                int pos = currentFragment.position();
                QString strText = currentFragment.text();
                for(int i = 0; i < strText.length(); i++)
                {
                    // 选择一个字, 随机设定颜色
                    QTextCharFormat fmt;
                    fmt.setForeground(_GetRamdomColor());
                    QTextCursor helper = cursor;
                    helper.setPosition(pos++);
                    helper.setPosition(pos, QTextCursor::KeepAnchor);
                    helper.setCharFormat(fmt);
                }
            }

        }

        currentBlock = currentBlock.next();
        if(!currentBlock.isValid())
            break;
    }
    // 光标移动到最后, 并设置拥有焦点
    QTextCursor c = ui.textEdit->textCursor();
    c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    ui.textEdit->setTextCursor(c);
    ui.textEdit->setFocus(Qt::MouseFocusReason);
}

//这段代码用于渲染QTextEdit为炫彩, 每个字随机分配一种颜色

//遍历的时候, 判断是图片还是文字. 并作相应的处理

//同时, 处理下QTextDocument的contentChange事件, 即可在键盘输入时, 就改变字的颜色

connect(document, SIGNAL(contentsChange( int , int , int )),
       this, SLOT(OnContentChange( int , int , int )));

void MyClass::OnContentChange( int position, int charsRemoved, int charsAdded )
{
    if(charsAdded == 0)
        return;

    QTextCursor cursor = ui.textEdit->textCursor();
    for (int i = 0; i < charsAdded; i++ )
    {
        int pos = position + i;
        // 选择一个字, 随机设定颜色
        QTextCharFormat fmt;
        fmt.setForeground(_GetRamdomColor());
        QTextCursor helper = cursor;
        helper.setPosition(pos);
        helper.setPosition(pos+1, QTextCursor::KeepAnchor);
        helper.setCharFormat(fmt);
    }

}
