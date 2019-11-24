#include "ProcessThread.h"
#include <QDebug>
#include <QImage>
#include <QString>
#include <QByteArray>
#include <string>
#include <QDir>
#include <QFile>

#include "TextRec.h"


ProcessThread::ProcessThread(const QString & filename)
    : m_strFilename(filename)
{

}


ProcessThread::~ProcessThread()
{

}


void ProcessThread::run()
{
    Mat bw;
    Mat dst;
    int wordcount = 0;
    Mat img = imread(m_strFilename.toStdString());
    if(img.empty())
    {
        //printf("Img is empty!\n");
        emit errorStringSignal("Image is empty!");
        return ;
    }
    if( !removeFolderContent("./Data/Step") )
    {
        emit errorStringSignal("Delete directory ./Data/Step Error!");
        return ;
    }
    // 文本图片字符分割
    CharacterSegmentation(img, bw, dst, &wordcount);

    qDebug() << "##### wordcount = " << wordcount << endl;
    QThread::sleep(3);
    readResultByWordCount(wordcount);
    emit displayStepsImageSignal();

    return;
}


bool ProcessThread::removeFolderContent(const QString & folderDir)
{
    QDir dir(folderDir);
    QFileInfoList fileList;
    QFileInfo curFile;
    if(!dir.exists())
    {
        return false;   //文件不存，则返回false
    }
    fileList = dir.entryInfoList(QDir::Dirs | QDir::Files
                                 | QDir::Readable | QDir::Writable
                                 | QDir::Hidden | QDir::NoDotAndDotDot
                                 , QDir::Name);
    while(fileList.size() > 0)
    {
        int infoNum = fileList.size();
        for(int i = infoNum - 1; i >= 0; i--)
        {
            curFile = fileList[i];
            if(curFile.isFile())//如果是文件，删除文件
            {
                QFile fileTemp(curFile.filePath());
                fileTemp.remove();
                fileList.removeAt(i);
            }
            if(curFile.isDir())//如果是文件夹
            {
                QDir dirTemp(curFile.filePath());
                QFileInfoList fileList1 = dirTemp.entryInfoList(QDir::Dirs | QDir::Files
                                          | QDir::Readable | QDir::Writable
                                          | QDir::Hidden | QDir::NoDotAndDotDot
                                          , QDir::Name);
                if(fileList1.size() == 0) //下层没有文件或文件夹
                {
                    dirTemp.rmdir(".");
                    fileList.removeAt(i);
                }
                else//下层有文件夹或文件
                {
                    for(int j = 0; j < fileList1.size(); j++)
                    {
                        if(!(fileList.contains(fileList1[j])))
                        {
                            fileList.append(fileList1[j]);
                        }
                    }
                }
            }
        }
    }
    return true;
}

void ProcessThread::readResultByWordCount(int wordcount)
{
    emit sendResutlTextSignal(QString::number(wordcount).toLocal8Bit());

}

