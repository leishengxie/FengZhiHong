
DEFINES += APPOINTMENT_DATASTREAM

HEADERS += $$PWD/net_appointments/NetAppointments.h \
    $$PWD/UserInfo.h \
    $$PWD/module_dairy/Dairy.h

SOURCES += $$PWD/net_appointments/NetAppointments.cpp \
    $$PWD/UserInfo.cpp \
    $$PWD/module_dairy/Dairy.cpp

contains(DEFINES, APPOINTMENT_DATASTREAM){
        INCLUDEPATH += $$PWD/net_appointments/datastream_type
        HEADERS += $$PWD/net_appointments/datastream_type/NetDataStream.h
}




