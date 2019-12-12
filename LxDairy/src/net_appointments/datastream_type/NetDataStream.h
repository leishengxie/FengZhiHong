#ifndef NET_DATASTREAM_H
#define NET_DATASTREAM_H

/////////////////////// QDateStrem //////////////////

class NetDataStream
{

};

//struct T_Student
//{
//    QString strName;
//    int nAge;

//    T_Student()
//    {

//    }

//    T_Student(QString strName, int nAge)
//        : strName(strName)
//        , nAge(nAge)
//    {

//    }


//#ifndef QT_NO_DATASTREAM
//    friend QDataStream & operator>>(QDataStream & in, T_Student & data);
//    friend QDataStream & operator<<(QDataStream & out, const T_Student & data);
//#endif

//};


//#ifndef QT_NO_DATASTREAM
//QDataStream & operator>>(QDataStream & in, T_Student & data)
//{
//    in >> data.strName >> data.nAge;
//    return in;
//}

//QDataStream & operator<<(QDataStream & out, const T_Student & data)
//{
//    out << data.strName << data.nAge;
//    return out;
//}
//#endif


//// --test ok
////Serializable
//T_Student tStudent("LiLei", 13);
//qDebug() << tStudent.strName << tStudent.nAge;

//QByteArray tmp_array;
//QDataStream out(&tmp_array, QIODevice::WriteOnly);
//out.setVersion(QDataStream::Qt_5_6);
////序列化对象信息
//out << tStudent;
//qDebug() << tmp_array;

//// DeSerializable
////读取文件流信息
//QByteArray tmp_array_de = tmp_array;
//QDataStream in(&tmp_array_de, QIODevice::ReadOnly);
//in.setVersion(QDataStream::Qt_5_6);
////反序列化，获取对象信息
//T_Student student_de;
//in >> student_de;

//qDebug() << student_de.strName << student_de.nAge;
// qDebug()<<__FILE__<<__FUNCTION__<<__LINE__<<endl;

#endif // NET_DATASTREAM_H
