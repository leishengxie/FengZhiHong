#ifndef RENAMEWIDGET_H
#define RENAMEWIDGET_H

#include <QWidget>

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
    void useZero(bool bUse); // 是否使用0占位

    //void addExtenBackClicked(bool checked);
   // void addExtenForeClicked(bool checked);

private slots:
//    QTabWidget* m_TabWidget;
//    QTableWidget* m_TableWidget;
    void initToolBar();
    void initTabWidget();
    void initTable();
    void addFile();
    void addFileToList(QString strFilePath);
    void delFile();
    void beginHandle();

private:
    Ui::CRenameWidget *ui;
    QList<T_FileMsg> m_lstFileMsg;
    QStandardItemModel* m_model;
    //int m_nOriginValue;
    bool m_bAddFore;

};

#endif // RENAMEWIDGET_H
