#ifndef RENAMEWIDGET_H
#define RENAMEWIDGET_H

#include <QWidget>
#include "OriginNum.h"

namespace Ui {
class CRenameWidget;
}

//class QTabWidget;
//class QTableWidget;
class QStandardItemModel;

struct T_FileMsg
{
    QString strFilePath;
    QString strDir;
    QString strFileName;
    QString strBaseName;
    QString strExtenName;
    QString strNewFileName;
    QString strNewBaseName;
    QString strNewExtenName;
    bool bHandle;
    T_FileMsg()
        : bHandle(false)
    {

    }
    QString newFileName()
    {
        strNewFileName = strNewBaseName + "." + strNewExtenName;
        return strNewFileName;
    }
    QString newFilePath()
    {
        return strDir + "/" + newFileName();
    }

};

class CRenameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CRenameWidget(QWidget *parent = 0);
    ~CRenameWidget();

    enum E_IncrementPos
    {
        EI_Front,   // 递增量在前部
        EI_Tail     // 递增量在尾部
    };

private slots:

    void update();
    void updateTableList();
    void updateDataList();
    void oldFileChanged(QString strOldFile);
    void originValueChanged(QString strOriginValue);
    void incrementChanged(int nIncrement);
    void addBackClicked(bool checked);
    void addForeClicked(bool checked);
    void replacePreviousChanged(QString strPrev);
    void replaceAfterChanged(QString strAfter);


    //void addExtenBackClicked(bool checked);
   // void addExtenForeClicked(bool checked);

private slots:
//    QTabWidget* m_TabWidget;
//    QTableWidget* m_TableWidget;
    void initButtons();
    void initTabWidget();
    void initTable();
    void addFile();
    void addFileToList(QString strFilePath);
    void delFile();
    void beginHandle();
    void onButtonGroupClicked(int id);

private:
    Ui::CRenameWidget *ui;
    QList<T_FileMsg> m_lstFileMsg;
    QStandardItemModel* m_model;

    COriginNum m_originNum;
    int m_nIncrement;   // 递增量
    E_IncrementPos m_eIncrementPos;    // 递增量是否在前面
    QString m_strNewBaseName;   // 新文件基础名
    // 替换
    QString m_strReplacePrevious;
    QString m_strReplaceAfter;

};

#endif // RENAMEWIDGET_H
