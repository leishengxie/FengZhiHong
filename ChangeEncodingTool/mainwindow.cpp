#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QTextCodec>
//#include <iostream>
#include <fstream>
#include "widgets/LToast.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *fileMenu = ui->menuBar->addMenu("file");
    fileMenu->addAction("打开目录");

    ui->mainToolBar->addAction("GBKToUtf-8");
    ui->mainToolBar->addAction("Utf-8ToGBK");
    ui->mainToolBar->addAction("去掉代码注释");
    connect(fileMenu,SIGNAL(triggered(QAction*)),this,SLOT(openFile(QAction*)));
    connect(ui->mainToolBar,SIGNAL(actionTriggered(QAction*)),this, SLOT(onToolBar(QAction*)));
    connect(ui->checkBoxC, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxCpp, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxH, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxLua, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxCC, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxHpp, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    connect(ui->checkBoxJava, SIGNAL(clicked()), this, SLOT(onCheckBox()));
    onCheckBox();


    ui->btnConvert->setEnabled(false);



    //ui->textSource->setText(QDir::currentPath());
    //use java to get
    QString str="GB2312,GBK,UTF-8,Big5,Big5-HKSCS,EUC-JP,EUC-KR,GB18030,IBM-Thai,IBM00858,IBM01140,IBM01141,IBM01142,IBM01143,IBM01144,IBM01145,IBM01146,IBM01147,IBM01148," \
                "IBM01149,IBM037,IBM1026,IBM1047,IBM273,IBM277,IBM278,IBM280,IBM284,IBM285,IBM297,IBM420,IBM424,IBM437,IBM500,IBM775,IBM850,IBM852,IBM855,IBM857,IBM860,IBM861,IBM862," \
                "IBM863,IBM864,IBM865,IBM866,IBM868,IBM869,IBM870,IBM871,IBM918,ISO-2022-CN,ISO-2022-JP,ISO-2022-JP-2,ISO-2022-KR,ISO-8859-1,ISO-8859-13,ISO-8859-15,ISO-8859-2," \
                "ISO-8859-3,ISO-8859-4,ISO-8859-5,ISO-8859-6,ISO-8859-7,ISO-8859-8,ISO-8859-9,JIS_X0201,JIS_X0212-1990,KOI8-R,KOI8-U,Shift_JIS,TIS-620,US-ASCII,UTF-16,UTF-16BE,UTF-16LE," \
                "UTF-32,UTF-32BE,UTF-32LE,UTF-8,windows-1250,windows-1251,windows-1252,windows-1253,windows-1254,windows-1255,windows-1256,windows-1257,windows-1258,windows-31j," \
                "x-Big5-HKSCS-2001,x-Big5-Solaris,x-euc-jp-linux,x-EUC-TW,x-eucJP-Open,x-IBM1006,x-IBM1025,x-IBM1046,x-IBM1097,x-IBM1098,x-IBM1112,x-IBM1122,x-IBM1123,x-IBM1124," \
                "x-IBM1381,x-IBM1383,x-IBM33722,x-IBM737,x-IBM833,x-IBM834,x-IBM856,x-IBM874,x-IBM875,x-IBM921,x-IBM922,x-IBM930,x-IBM933,x-IBM935,x-IBM937,x-IBM939,x-IBM942,x-IBM942C," \
                "x-IBM943,x-IBM943C,x-IBM948,x-IBM949,x-IBM949C,x-IBM950,x-IBM964,x-IBM970,x-ISCII91,x-ISO-2022-CN-CNS,x-ISO-2022-CN-GB,x-iso-8859-11,x-JIS0208,x-JISAutoDetect," \
                "x-Johab,x-MacArabic,x-MacCentralEurope,x-MacCroatian,x-MacCyrillic,x-MacDingbat,x-MacGreek,x-MacHebrew,x-MacIceland,x-MacRoman,x-MacRomania,x-MacSymbol,x-MacThai," \
                "x-MacTurkish,x-MacUkraine,x-MS932_0213,x-MS950-HKSCS,x-MS950-HKSCS-XP,x-mswin-936,x-PCK,x-SJIS_0213,x-UTF-16LE-BOM,X-UTF-32BE-BOM,X-UTF-32LE-BOM,x-windows-50220," \
                "x-windows-50221,x-windows-874,x-windows-949,x-windows-950,x-windows-iso2022jp";
        QList<QByteArray> listCodecs = QTextCodec::availableCodecs();
        str = listCodecs.join(',');
        //qDebug() << "GBK" << list.contains("GBK");
        //qDebug() << "UTF-8" << codec->canEncode("UTF-8");
    QStringList list=str.split(",");
   // QStringList list = listCodecs;
    ui->srcComboBox->addItems(list);
    ui->srcComboBox->setCurrentIndex(0);
    ui->destComboBox->addItems(list);;
    ui->destComboBox->setCurrentIndex(5);
    setWindowTitle("ChangeEncoding");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onToolBar(QAction *action)
{
    if (action->text() == "Utf-8ToGBK")
    {
        allChildFile_Utf8ToGBK(m_strOpenPath);
    }
    else if (action->text() == "GBKToUtf-8")
    {
        allChildFile_GBKToUtf8(m_strOpenPath);
    }
    else if (action->text() == "去掉代码注释")
    {
        deleteComments(m_strOpenPath);
    }
}

void MainWindow::onCheckBox()
{
    m_strlstExpandedName.clear();
    if (ui->checkBoxC->isChecked())
    {
        m_strlstExpandedName.append("c");
    }
    if (ui->checkBoxCpp->isChecked())
    {
        m_strlstExpandedName.append("cpp");
    }
    if (ui->checkBoxH->isChecked())
    {
        m_strlstExpandedName.append("h");
    }
    if (ui->checkBoxLua->isChecked())
    {
        m_strlstExpandedName.append("lua");
    }
    if (ui->checkBoxHpp->isChecked())
    {
        m_strlstExpandedName.append("hpp");
    }
    if (ui->checkBoxCC->isChecked())
    {
        m_strlstExpandedName.append("cc");
    }
    if (ui->checkBoxJava->isChecked())
    {
        m_strlstExpandedName.append("java");
    }
    qDebug() << m_strlstExpandedName;
}

void toUtf8()
{
    //    QRegExp rx("\"([^\".]*[\u4e00-\u9fa5]+[^\".]*)+\"");//正则表达式，匹配含有中文的字符串，带""
    //    QFile fileWrite(fileName);
    //   QTextStream txtStream(&fileName);
    //    txtStream.setCodec("UTF-8");
    //    if(!fileWrite.open(QIODevice::WriteOnly))
    //    {
    //    continue;
    //    }
    //    ...//匹配字符串，然后加上EVTR
    //    fileWrite.write(txtStr.toUtf8());  //txtStr是我修改好的内容要重新写入文件的字符串
    //    fileWrite.close();

    QFile file("FileName");

    QTextCodec *codec = QTextCodec::codecForName("GBK");

    QString line = codec->toUnicode(file.readLine());
}

void MainWindow::GBKToUtf8Fun1(QString strFilePath)
{
    QString strCodecSrc = ui->srcComboBox->currentText();
    QString dstrCodecDest = ui->destComboBox->currentText();

    srcCodec = QTextCodec::codecForName(strCodecSrc.toLatin1());
    destCodec = QTextCodec::codecForName(dstrCodecDest.toLatin1());

    //----1
    QFile file(strFilePath);
    bool ok = file.open(QIODevice::ReadWrite | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    QTextStream io(&file);
    io.setCodec(srcCodec);
    QString strAll= io.readAll();
    qDebug() << "strAll=" << strAll;
    io.seek(0);
    io.setCodec("UTF-8");
    //io.setGenerateByteOrderMark(true);
    io << strAll;
    file.close();

//    //-----2
//    QFile srcFile(strFilePath);
//    bool ok = srcFile.open(QIODevice::ReadOnly);
//    if(!ok)
//    {
//        qDebug() << "open file fail:" + strFilePath;
//        return;
//    }
//    QTextStream in(&srcFile);
//    in.setAutoDetectUnicode(false);
//    in.setCodec(srcCodec);
//    QString tmpStr = in.readAll();
//    srcFile.close();

//    QFile dstFile(strFilePath);
//    ok = dstFile.open(QIODevice::WriteOnly);
//    if(!ok)
//    {
//        qDebug() << "open file fail:" + strFilePath;
//        return;
//    }
//    QTextStream out(&dstFile);
//    out.setAutoDetectUnicode(false);
//    out.setCodec(destCodec);
//    out<<tmpStr;
//    dstFile.close();
}


// 通常做法是src文件用该原有的编码打开，dest文件用需要转换的编码写入
// 当前src文件和dest文件相同时，记得关闭打开的文件，重新打开写入
void MainWindow::GBKToUtf8(QString strFilePath)
{
    QFile file(strFilePath);
    bool ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName("GBK"); //设置codec为GBK编码
    QByteArray byteArrStr = file.readAll();
    file.close();
    // 防止空文件
    if (byteArrStr.isEmpty())
    {
        qDebug() << "file is empty";
        return;
    }
    if (getEncodingType(byteArrStr) == EE_Utf_8)
    {
        qDebug() << "file already utf-8 code";
        return;
    }
    QString strAll= codec->toUnicode(byteArrStr); //将codec的GBK的字符串转换为Unicode
    qDebug() << "strAll=" << strAll;

    QFile filewrite(strFilePath);
    ok = filewrite.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    filewrite.seek(0);
    filewrite.write(strAll.toUtf8().data());
    filewrite.close();
}

void MainWindow::Utf8ToGBK(QString strFilePath)
{
    QFile file(strFilePath);
    bool ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    QTextCodec *codecUtf8 = QTextCodec::codecForName("UTF-8"); //设置codec为GBK编码
    QByteArray byteArrStr = file.readAll();
    file.close();
    // 防止空文件
    if (byteArrStr.isEmpty())
    {
        qDebug() << "file is empty";
        return;
    }
    if (getEncodingType(byteArrStr) != EE_Utf_8)
    {
        qDebug() << "file codec is not utf-8 code";
        return;
    }
    QString strAll= codecUtf8->toUnicode(byteArrStr); //将codec的GBK的字符串转换为Unicode
    qDebug() << "strAll=" << strAll;

    QFile filewrite(strFilePath);
    ok = filewrite.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    filewrite.seek(0);
    filewrite.write(strAll.toLocal8Bit().data());
    filewrite.close();
}

void MainWindow::allChildFile_GBKToUtf8(QString strPath)
{
    QDir dir(strPath);
    if (!dir.exists())
    {
        qDebug()<< "the dir:" << strPath << "is not exists";
        return;
    }
    //QStringList filter;  // 设置文件过滤器
    //filter<<"*.h";
    //filter<<"*.cpp";
    dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉
    dir.setSorting(QDir::DirsFirst);//优先显示目录
    //dir.setNameFilters(filter);
    QFileInfoList lstFileInfo = dir.entryInfoList();//获取文件信息列表 // QFileInfoList lstFileInfo = dir.entryInfoList(filter,QDir::Dirs|QDir::Files,QDir::DirsFirst);
    foreach(QFileInfo fileInfo ,lstFileInfo)
    {
        if(fileInfo.isFile())
        {
            QString strSuffix= fileInfo.suffix(); //获取文件后缀名
            if (ui->checkBoxAll->isChecked())
            {
                GBKToUtf8(fileInfo.filePath());
            }
            else if (m_strlstExpandedName.contains(strSuffix))
            {
                qDebug()<< "File :" << fileInfo.fileName();
                ui->textBrowser->append(fileInfo.fileName());
                GBKToUtf8(fileInfo.filePath());
            }
        }
        else
        {
            if(fileInfo.fileName()=="." || fileInfo.fileName() == "..")
            {
                continue;
            }
            qDebug() << "Entry Dir" << fileInfo.absoluteFilePath();
            allChildFile_GBKToUtf8(fileInfo.absoluteFilePath()); //递归
        }
    }

    CLToast * test_case_014 = new CLToast(this, "转换完毕");
    test_case_014->toastr();
}



void MainWindow::allChildFile_Utf8ToGBK(QString strPath)
{
    QDir dir(strPath);
    if (!dir.exists())
    {
        qDebug()<< "the dir:" << strPath << "is not exists";
        return;
    }
    //QStringList filter;  // 设置文件过滤器
    //filter<<"*.h";
    //filter<<"*.cpp";
    dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉
    dir.setSorting(QDir::DirsFirst);//优先显示目录
    //dir.setNameFilters(filter);
    QFileInfoList lstFileInfo = dir.entryInfoList();//获取文件信息列表 // QFileInfoList lstFileInfo = dir.entryInfoList(filter,QDir::Dirs|QDir::Files,QDir::DirsFirst);
    foreach(QFileInfo fileInfo ,lstFileInfo)
    {
        if(fileInfo.isFile())
        {
            QString strSuffix= fileInfo.suffix(); //获取文件后缀名
            if (ui->checkBoxAll->isChecked()) //是否全选
            {
                Utf8ToGBK(fileInfo.filePath());
            }
            else if (m_strlstExpandedName.contains(strSuffix))
            {
                qDebug()<< "File :" << fileInfo.fileName();
                ui->textBrowser->append(fileInfo.fileName());
                Utf8ToGBK(fileInfo.filePath());
            }
        }
        else
        {
            if(fileInfo.fileName()=="." || fileInfo.fileName() == "..")
            {
                continue;
            }
            qDebug() << "Entry Dir" << fileInfo.absoluteFilePath();
            allChildFile_Utf8ToGBK(fileInfo.absoluteFilePath()); //递归
        }
    }

    //    文件数目：fileInfo->count();
    //    文件名称：fileInfo->at(i).fileName();
    //    文件路径（包含文件名）：fileInfo->at(i).filePath();
}

bool FindFile(const QString & path)
{
    QDir dir(path);
    if (!dir.exists())
    {
        return false;
    }
    dir.setFilter(QDir::Dirs|QDir::Files);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    int i = 0;
    int nFiles = 0;
    bool bIsDir;
    do{
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName()=="."|fileInfo.fileName()=="..")
        {
            i++;
            continue;
        }
        bIsDir = fileInfo.isDir();
        if (bIsDir)
        {
            nFiles++;                //对文件属性进行处理
            //fileInfo.size(),fileInfo.fileName(),fileInfo.path()
            FindFile(fileInfo.filePath());
        }
        else
        {
            nFiles++;
        }
        i++;
    }
    while(i<list.size());
}

/*
//获取文件前缀名
QFileInfo fi("/tmp/archive.tar.gz");
QString base= fi.baseName(); // base = "archive"
//获取文件的完整前缀名
 QFileInfo fi("/tmp/archive.tar.gz");
QString base= fi.completeBaseName(); // base = "archive.tar"
//获取文件后缀名
QFileInfo fi("/tmp/archive.tar.gz");
QString ext= fi.suffix();  // ext = "gz"
//获取文件的完整后缀名
QFileInfo fi("/tmp/archive.tar.gz");
QString ext= fi.completeSuffix(); // ext = "tar.gz"
*/

void MainWindow::deleteComments(QString strPath)
{
    QDir dir(strPath);
    if (!dir.exists())
    {
        qDebug()<< "the dir:" << strPath << "is not exists";
        return;
    }
    dir.setFilter(QDir::Dirs|QDir::Files);//除了目录或文件，其他的过滤掉
    dir.setSorting(QDir::DirsFirst);//优先显示目录
    QFileInfoList lstFileInfo = dir.entryInfoList();//获取文件信息列表 // QFileInfoList lstFileInfo = dir.entryInfoList(filter,QDir::Dirs|QDir::Files,QDir::DirsFirst);
    foreach(QFileInfo fileInfo ,lstFileInfo)
    {
        if(fileInfo.isFile())
        {
            QString strSuffix= fileInfo.suffix(); //获取文件后缀名
            if (ui->checkBoxAll->isChecked()) //是否全选
            {
                deleteCommentsRow(fileInfo.filePath());
            }
            else if (m_strlstExpandedName.contains(strSuffix))
            {
                qDebug()<< "File :" << fileInfo.fileName();
                ui->textBrowser->append(fileInfo.fileName());
                deleteCommentsRow(fileInfo.filePath());
            }
        }
        else
        {
            if(fileInfo.fileName()=="." || fileInfo.fileName() == "..")
            {
                continue;
            }
            qDebug() << "Entry Dir" << fileInfo.absoluteFilePath();
            deleteComments(fileInfo.absoluteFilePath()); //递归
        }
    }
}

void MainWindow::deleteCommentsRow(QString strFilePath)
{
    QFile file(strFilePath);
    bool ok = file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    QString strContent = file.readAll();
    QRegExp rx("//[^\n]*"); //包含\n之外的一切字符
    //^((?!hede).)*$   //不包含hede
    //QRegExp rx("^((?!https:).)*$//[^\n]*"); //包含\n之外的一切字符
    strContent.replace(rx, "");
    file.close();
    QFile filewrite(strFilePath);
    ok = filewrite.open(QIODevice::WriteOnly | QIODevice::Text);
    if(!ok)
    {
        qDebug() << "open file fail:" + strFilePath;
        return;
    }
    filewrite.seek(0);
    filewrite.write(strContent.toStdString().c_str());
    filewrite.close();
}

void MainWindow::codeType()
{
    //test

    ifstream fin("C:/Users/Administrator/Desktop/w/1.cpp",ios::binary);
    unsigned char  s2;
    fin.read((char*)&s2, sizeof(s2));//读取第一个字节，然后左移8位
    int p = s2<<8;
    fin.read((char*)&s2, sizeof(s2));//读取第二个字节
    p +=s2;

    string code;

    switch(p)//判断文本前两个字节
    {
    case 0xfffe:  //65534
        code = "Unicode";
        break;
    case 0xfeff://65279
        code = "Unicode big endian";
        break;
    case 0xefbb://61371
        code = "UTF-8";
        break;
    default:
        code = "ANSI";
    }
    fin.close();
    return;
}

E_EncodingType MainWindow::getEncodingType(QByteArray byteArrStr)
{
    unsigned char ch = byteArrStr.at(0);
    int nVar = ch << 8;
    ch = byteArrStr.at(1);
    nVar += ch;
    switch(nVar)//判断文本前两个字节
    {
    case 0xfffe:  //65534
        return EE_Unicode;
    case 0xfeff://65279
        return EE_UnicodeBigEndian;
    case 0xefbb://61371
        return EE_Utf_8;
    default:
        return (isTextUTF8(byteArrStr.data(), byteArrStr.size()) ?  EE_Utf_8 : EE_ANSI);
    }
    return EE_ANSI;
}

bool MainWindow::isTextUTF8(const char* str,long length)
{
    int i;
    int nBytes=0;//UFT8可用1-6个字节编码,ASCII用一个字节
    unsigned char chr;
    bool bAllAscii=true; //如果全部都是ASCII, 说明不是UTF-8
    for(i=0;i<length;i++)
    {
        chr= *(str+i);
        if( (chr&0x80) != 0 ) // 判断是否ASCII编码,如果不是,说明有可能是UTF-8,ASCII用7位编码,但用一个字节存,最高位标记为0,o0xxxxxxx
            bAllAscii= false;
        if(nBytes==0) //如果不是ASCII码,应该是多字节符,计算字节数
        {
            if(chr>=0x80)
            {
                if(chr>=0xFC&&chr<=0xFD)
                    nBytes=6;
                else if(chr>=0xF8)
                    nBytes=5;
                else if(chr>=0xF0)
                    nBytes=4;
                else if(chr>=0xE0)
                    nBytes=3;
                else if(chr>=0xC0)
                    nBytes=2;
                else
                {
                    return false;
                }
                nBytes--;
            }
        }
        else //多字节符的非首字节,应为 10xxxxxx
        {
            if( (chr&0xC0) != 0x80 )
            {
                return false;
            }
            nBytes--;
        }
    }

    if( nBytes > 0 ) //违返规则
    {
        return false;
    }

    if( bAllAscii ) //如果全部都是ASCII, 说明不是UTF-8
    {
        return false;
    }
    return true;
}

void MainWindow::openFile(QAction *action)
{

    m_strOpenPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "../",
                                                      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->textBrowser->setText("打开文件路径:" + m_strOpenPath);
}


//// 列表文件增加 BOM
//for (auto it = lst.begin(); it != lst.end(); it++)
//{
//    FILE* f = fopen(it->wholePath.c_str(), "rb");
//    if (!f) {
//        cerr << "Error: Cannot open" << it->wholePath << endl;
//        continue;
//    }
//    unsigned char buf[10];
//    fread(buf, 1, 3, f);

//    // Get file size:
//    fseek(f, 0, SEEK_END);
//    const long N = ftell(f);
//    fclose(f);

//    if (buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF) {
//        cout  << "Skipping (already has BOM): " << it->wholePath << endl;
//        continue;
//    }

//    // Add BOM: =======================================
//    // Read the whole file:
//    unsigned char* fil_buf = new unsigned char[N + 3];
//    fil_buf[0] = 0xEF;
//    fil_buf[1] = 0xBB;
//    fil_buf[2] = 0xBF;

//    f = fopen(it->wholePath.c_str(), "rb");
//    fread(fil_buf + 3, 1, N, f);
//    fclose(f);

//    // Write new version:
//    f = fopen(it->wholePath.c_str(), "wb");
//    fwrite(fil_buf, 1, N + 3, f);
//    fclose(f);

//    delete[] fil_buf;

//    cout << "Added BOM: " << it->wholePath << endl;
//}


//// 列表文件移除 BOM
//for (auto it it = lst.begin(); it != lst.end(); it++)
//{
//    FILE* f = fopen(it->wholePath.c_str(), "rb");
//    if (!f) {
//        cerr << "Error: Cannot open" << it->wholePath << endl;
//        continue;
//    }
//    unsigned char buf[10];
//    fread(buf, 1, 3, f);

//    // Get file size:
//    fseek(f, 0, SEEK_END);
//    const long N = ftell(f);
//    fclose(f);

//    if (!(buf[0] == 0xEF && buf[1] == 0xBB && buf[2] == 0xBF)) {
//        cout  << "Skipping (has no BOM): " << it->wholePath << endl;
//        continue;
//    }

//    // Remove BOM: =======================================
//    // Read the whole file:
//    unsigned char* fil_buf = new unsigned char[N];

//    f = fopen(it->wholePath.c_str(), "rb");
//    fread(fil_buf, 1, N, f);
//    fclose(f);

//    // Write new version:
//    f = fopen(it->wholePath.c_str(), "wb");
//    fwrite(fil_buf + 3, 1, N - 3, f);
//    fclose(f);

//    delete[] fil_buf;

//    cout << "Removed BOM: " << it->wholePath << endl;
//}




