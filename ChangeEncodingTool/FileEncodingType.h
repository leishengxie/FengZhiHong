#ifndef CFILEENCODINGTYPE_H
#define CFILEENCODINGTYPE_H
#include <QString>
#include <QDebug>



class IFileEncodingType
{

public:
    enum E_TypeIndex
    {
        ET_Invalid = -1,
        ET_Ansi,
        ET_Utf8,
        ET_Unicode,
        ET_UnicodeBig
    };

    virtual QString typeName()
    {
        return "";
    }
    virtual int typeIndex()
    {
        return ET_Invalid;
    }
    virtual ~IFileEncodingType()
    {
        qDebug() << "FileType disconstraction called!";
    }
};


///
/// \brief The CAsciiFileType class
///
class CAsciiFileType: public IFileEncodingType
{

public:
    QString typeName() override
    {

        return "ANSI";
    }

    int typeIndex()
    {
        return ET_Ansi;
    }
};

class CUtf8FileType: public IFileEncodingType
{

public:
    QString typeName() override
    {

        return "UTF-8";
    }
    int typeIndex()
    {
        return ET_Utf8;
    }
};

class CUniFileType: public IFileEncodingType
{

public:
    QString typeName() override
    {

        return "Unicode";
    }
    int typeIndex()
    {
        return ET_Unicode;
    }
};

class CUniBigFileType: public IFileEncodingType
{

public:
    QString typeName() override
    {

        return "Unicode big endian";
    }
    int typeIndex()
    {
        return ET_UnicodeBig;
    }
};




#endif // CFILEENCODINGTYPE_H
