#ifndef CFILEENCODINGTYPEFACOTRY_H
#define CFILEENCODINGTYPEFACOTRY_H
#include "FileEncodingType.h"

class CFileEncodingTypeFacotry
{
public:
    static IFileEncodingType *createFileEncodingType(QByteArray byteArray)
    {

        IFileEncodingType *fileEncodingType;

        if(byteArray == "\xEF\xBB"){    //UTF-8

            fileEncodingType = new CUtf8FileType;
        }
        else if(byteArray == "\xFF\xFE"){       //Unicode

            fileEncodingType = new CUniFileType;
        }
        else if(byteArray == "\xFE\xFF"){       //Unicode big endian

            fileEncodingType = new CUniBigFileType;
        }
        else{

            fileEncodingType = new CAsciiFileType;
        }


        return fileEncodingType;
    }
};



#endif // CFILEENCODINGTYPEFACOTRY_H


//void DisposeFile::transformFile(const QString &sourceFile)
//{
//    QFile file(sourceFile);
//    if(!file.open(QIODevice::ReadOnly)){

//        qDebug() << "open failed!";
//        return;
//    }

//    QByteArray byteArray = file.readAll();
//    //qDebug() << "byteArray:" << QString::frombyteArray;

//    FileType *fileType = FileTypeFactory::createFileTypeFactory(byteArray.left(2));

//    GenDialog *genDialog = new GenDialog(NULL ,m_currentFileName, fileType->getFileType());
//    if(genDialog->exec() == QDialog::Accepted){

//        QString head = genDialog->getArmStr();

//        saveFile(head, fileType->getFileType(),byteArray);
//    }
//    delete genDialog;

//    delete fileType;

//    file.close();
//}

//if(head == "ASCII"){

//    if(sourceCode == "UTF-8"){

//        file.write(QString::fromUtf8(data).toStdString().c_str());
//    }
//    else{

//        file.write(QString::fromLocal8Bit(data).toStdString().c_str());
//    }
//}
//else{

//    if(sourceCode == "UTF-8"){

//        file.write("\xEF\xBB\xBF");
//        file.write(QString::fromUtf8(data).toStdString().c_str());
//    }
//    else{

//        file.write("\xEF\xBB\xBF");
//        file.write(QString::fromLocal8Bit(data).toStdString().c_str());
//    }
//}
