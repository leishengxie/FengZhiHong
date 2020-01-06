
DEFINES += APPOINTMENT_DATASTREAM

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/net_appointments
INCLUDEPATH += $$PWD/module_collection
INCLUDEPATH += $$PWD/module_dairy

HEADERS += $$PWD/net_appointments/NetAppointments.h \
    $$PWD/UserInfo.h \
    $$PWD/module_dairy/Dairy.h \
    $$PWD/module_collection/collection_jokebook/Joke.h \
    $$PWD/DairyHttpClient.h

SOURCES += $$PWD/net_appointments/NetAppointments.cpp \
    $$PWD/UserInfo.cpp \
    $$PWD/module_dairy/Dairy.cpp \
    $$PWD/module_collection/collection_jokebook/Joke.cpp \
    $$PWD/DairyHttpClient.cpp

contains(DEFINES, APPOINTMENT_DATASTREAM){
        INCLUDEPATH += $$PWD/net_appointments/datastream_type
        HEADERS += $$PWD/net_appointments/datastream_type/NetDataStream.h
}




