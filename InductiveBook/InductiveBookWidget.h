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

    void OnTest();
    void OnContentChange( int position, int charsRemoved, int charsAdded );
    void onCurrentCharFormatChanged(const QTextCharFormat & charFormat);

private slots:
    void mergeFormat(QTextCharFormat fmt);
    void bold(bool bBold);

    void on_switchButton_checkedChanged(bool bChecked);

private:
    void showInductive();

private:
    Ui::CInductiveBookWidget *ui;

    COcrHandleWidget* m_pOcrHandleWidget;

    QTextDocument* m_docBackup;

    int m_nFontWeightInductive;
    QColor m_ColorInductive;
};

#endif // INDUCTIVEBOOKWIDGET_H
