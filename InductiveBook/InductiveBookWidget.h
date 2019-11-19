#ifndef INDUCTIVEBOOKWIDGET_H
#define INDUCTIVEBOOKWIDGET_H

#include <QWidget>
#include <QTextCharFormat>

namespace Ui {
class CInductiveBookWidget;
}

class COcrHandleWidget;

class CInductiveBookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CInductiveBookWidget(QWidget *parent = 0);
    ~CInductiveBookWidget();

public slots:
    void addInductiveArticle();

private slots:
    void mergeFormat(QTextCharFormat fmt);
    void bold(bool bBold);

private:
    Ui::CInductiveBookWidget *ui;

    COcrHandleWidget* m_pOcrHandleWidget;
};

#endif // INDUCTIVEBOOKWIDGET_H
