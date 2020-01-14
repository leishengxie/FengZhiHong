
#may be these condition about loading files is not used.
DEFINES += APPOINTMENT_DATASTREAM
#DEFINES += APPOINTMENT_JSON
#DEFINES += APPOINTMENT_PROTOBUFF

#DEFINES += APPOINTMENT_TYPE = APPOINTMENT_DATASTREAM

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/net_appointments
INCLUDEPATH += $$PWD/module_collection

HEADERS += $$PWD/net_appointments/NetAppointments.h \
    $$PWD/module_collection/collection_jokebook/Joke.h \
    $$PWD/UserInfo.h \
    $$PWD/module_dairy/Dairy.h

SOURCES += $$PWD/net_appointments/NetAppointments.cpp \
    $$PWD/module_collection/collection_jokebook/Joke.cpp \
    $$PWD/UserInfo.cpp \
    $$PWD/module_dairy/Dairy.cpp

contains(DEFINES, APPOINTMENT_DATASTREAM){
        INCLUDEPATH += $$PWD/net_appointments/datastream_type
        HEADERS += $$PWD/net_appointments/datastream_type/NetDataStream.h
}

#contains(DEFINES, APPOINTMENT_JSON){
#        INCLUDEPATH += $$PWD/json_type
#        HEADERS += $$PWD/json_type/NetJson.h
#}

#contains(DEFINES, APPOINTMENT_PROTOBUFF){
#        INCLUDEPATH += $$PWD/protobuff_type
#        HEADERS += $$PWD/protobuff_type/NetProtobuff.h
#}

