#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum E_EncodingType
{
    EE_ANSI,                 //无格式定义  对于中文编码格式是GB2312,GBK等;
    EE_Unicode, //文本里前两个字节为FF FE   字节流是little endian
    EE_UnicodeBigEndian, //文本里前两个字节为FE FF   字节流是big  endian
    EE_Utf_8, //前两字节为EF BB，第三字节为BF 带bom
    EE_Invalid
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile(QAction* action);
    void onToolBar(QAction* action);
    void onCheckBox();

private:
    void GBKToUtf8Fun1(QString strFilePath);
    void GBKToUtf8(QString strFilePath);
    void Utf8ToGBK(QString strFilePath);

    void allChildFile_GBKToUtf8(QString strPath);
    void allChildFile_Utf8ToGBK(QString strPath);
    //去掉注释
    void deleteComments(QString strPath);
    void deleteCommentsRow(QString strPath);

    void codeType();
    bool isTextUTF8(const char* str,long length);
    E_EncodingType getEncodingType(QByteArray byteArrStr);

private:
    Ui::MainWindow *ui;
    QString m_strOpenPath;
    QStringList m_strlstExpandedName;

    QTextCodec *srcCodec;
    QTextCodec *destCodec;
    QString srcFileName;        //源文件名
    QString destFileName;       //目标文件名
};

#endif // MAINWINDOW_H
