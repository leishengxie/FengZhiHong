#include "InductiveBookWidget.h"
#include "ui_InductiveBookWidget.h"
#include <QListView>
#include <QTextFormat>
#include <QTextBlock>
#include <QStack>
#include "OcrHandleWidget.h"

CInductiveBookWidget::CInductiveBookWidget(QWidget* parent) :
    QWidget(parent),
    ui(new Ui::CInductiveBookWidget)
    , m_pOcrHandleWidget(new COcrHandleWidget)
    , m_nFontWeightInductive(QFont::Bold)
    , m_ColorInductive(QColor(100, 184, 255))
{
    ui->setupUi(this);
    //QListView

    ui->checkButton->setText("标记归纳文本");
    connect(ui->checkButton, SIGNAL(clicked(bool)), this, SLOT(bold(bool)));
    connect(ui->btnOcr, SIGNAL(clicked()), m_pOcrHandleWidget, SLOT(show()));
    connect(ui->listView, SIGNAL(btnAddClicked()), this, SLOT(addInductiveArticle()));

//    QTextDocument* document = ui->textEdit->document();
//    connect(document, SIGNAL(contentsChange( int, int, int )), this
//    , SLOT(OnContentChange( int, int, int )));

    connect(ui->textEdit, SIGNAL(currentCharFormatChanged(QTextCharFormat))
            , this, SLOT(onCurrentCharFormatChanged(QTextCharFormat)));
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
        //cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
}

void CInductiveBookWidget::bold(bool bBold)
{
    QTextCharFormat charFormat;
    //fmt.setFontItalic(bBold); 斜体
    if (bBold)
    {

        charFormat.setFontWeight(m_nFontWeightInductive);
        charFormat.setForeground(m_ColorInductive);
    }
    else
    {
        charFormat.setFontWeight(QFont::Normal);
        charFormat.setForeground(Qt::black);
    }
    mergeFormat(charFormat);

}


//3. 如何遍历QTextEdit中的内容

//　　QTextEdit中的内容实际上是由QTextDocument维护

//　　可以简单的理解: QTextDocument 包含 N个QTexBlock(段落), 每个QTexBlock包含N个QTextFragment

QColor getRamdomColor()
{
    QColor col;
    int RamdomNum = rand() % 0xffffff;
    char strCol[8];
    sprintf(strCol, "#%06x", RamdomNum);
    col.setNamedColor(QString::fromLocal8Bit(strCol, 8));
    return col;
}


///
/// \brief CInductiveBookWidget::OnTest
///
void CInductiveBookWidget::OnTest()
{
    QTextDocument* document = ui->textEdit->document();
    QTextBlock blockCur = document->begin();
    QTextBlock::iterator it;
    QTextCursor cursor = ui->textEdit->textCursor();

    while( true)
    {
        // 在修改chatformat时会改变当前Block的fragment
        // 所以++it的处理类似std::map中的erase操作
        for (it = blockCur.begin(); it != blockCur.end(); )
        {
            QTextFragment fragmentCur = it.fragment();
            // 判断出这个fragment为image
            if (fragmentCur.charFormat().isImageFormat())
            {
                ++it;
                continue;
            }


            if (fragmentCur.isValid())
            {
                ++it;
                int pos = fragmentCur.position();
                QString strText = fragmentCur.text();
                for(int i = 0; i < strText.length(); i++)
                {
                    // 选择一个字, 随机设定颜色
                    QTextCharFormat fmt;
                    fmt.setForeground(getRamdomColor());
                    QTextCursor helper = cursor;
                    helper.setPosition(pos++);
                    helper.setPosition(pos, QTextCursor::KeepAnchor);
                    helper.setCharFormat(fmt);
                }
            }

        }

        blockCur = blockCur.next();
        if(!blockCur.isValid())
        {
            break;
        }
    }
    // 光标移动到最后, 并设置拥有焦点
    QTextCursor c = ui->textEdit->textCursor();
    c.movePosition(QTextCursor::End, QTextCursor::MoveAnchor);
    ui->textEdit->setTextCursor(c);
    ui->textEdit->setFocus(Qt::MouseFocusReason);

    //这段代码用于渲染QTextEdit为炫彩, 每个字随机分配一种颜色
    //遍历的时候, 判断是图片还是文字. 并作相应的处理
    //同时, 处理下QTextDocument的contentChange事件, 即可在键盘输入时, 就改变字的颜色



}


void CInductiveBookWidget::OnContentChange( int position, int charsRemoved, int charsAdded )
{
    if(charsAdded == 0)
    {
        return;
    }

    QTextCursor cursor = ui->textEdit->textCursor();
    for (int i = 0; i < charsAdded; i++ )
    {
        int pos = position + i;
        // 选择一个字, 随机设定颜色
        QTextCharFormat fmt;
        fmt.setForeground(getRamdomColor());
        QTextCursor cursorTemp = cursor;
        cursorTemp.setPosition(pos);
        cursorTemp.setPosition(pos + 1, QTextCursor::KeepAnchor);
        cursorTemp.setCharFormat(fmt);
    }

}

void CInductiveBookWidget::onCurrentCharFormatChanged(const QTextCharFormat &charFormat)
{
    ui->checkButton->setChecked(m_nFontWeightInductive == charFormat.fontWeight());
}

void CInductiveBookWidget::on_switchButton_checkedChanged(bool bChecked)
{
    if (bChecked)
    {
        QTextDocument* document = ui->textEdit->document();
        m_docBackup = document->clone(ui->textEdit);    // 并指定父对象
        showInductive();
        ui->textEdit->setEnabled(false);
    }
    else
    {
        //译文：编辑器不接受文档的所有权，除非它是文档的父对象。所提供文档的父对象仍然是对象的所有者。
        //如果先前分配的文档是编辑器的子文档，那么它将被删除。
        ui->textEdit->setDocument(m_docBackup);
        //document->deleteLater();
        ui->textEdit->setEnabled(true);
    }
}

struct T_NodeDelete
{
    int nPosStart;
    int nPosEnd;

    T_NodeDelete()
        : nPosStart(0)
        , nPosEnd(0)
    {

    }

    T_NodeDelete(int nPosStart, int nPosEnd)
        : nPosStart(nPosStart)
        , nPosEnd(nPosEnd)
    {

    }

};


///
/// \brief CInductiveBookWidget::showInductive  显示归纳的文本
/// QTextEdit中的内容实际上是由QTextDocument维护，遍历QTextEdit中的内容
/// 可以简单的理解: QTextDocument 包含 N个QTexBlock(段落), 每个QTexBlock包含N个QTextFragment
///
void CInductiveBookWidget::showInductive()
{
    QTextDocument* document = ui->textEdit->document();
    QTextBlock blockCur = document->begin();
    QTextBlock::iterator it;
    QTextCursor cursor = ui->textEdit->textCursor();
    QStack<T_NodeDelete> stackNode;

    while( true)
    {
        for (it = blockCur.begin(); it != blockCur.end(); ++it)
        {

            QTextFragment fragmentCur = it.fragment();
            QTextCharFormat charFormat = fragmentCur.charFormat();
            if (charFormat.isValid())
            {
                if ( m_nFontWeightInductive == charFormat.fontWeight()
                        && m_ColorInductive == charFormat.foreground().color())
                {

                }
                else
                {
                    stackNode.push(T_NodeDelete(fragmentCur.position(), fragmentCur.position() + fragmentCur.length()));

                }
            }
        }

        blockCur = blockCur.next();
        if(!blockCur.isValid())
        {
            break;
        }
    }

    // 从后往前删
    while (!stackNode.isEmpty())
    {
        T_NodeDelete tNode = stackNode.pop();
        cursor.setPosition(tNode.nPosStart);
        cursor.setPosition(tNode.nPosEnd, QTextCursor::KeepAnchor);
        cursor.removeSelectedText();
    }

}

void CInductiveBookWidget::on_btnOcr_clicked()
{

}
