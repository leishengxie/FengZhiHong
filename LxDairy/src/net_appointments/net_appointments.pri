
DEFINES += APPOINTMENT_DATASTREAM
DEFINES += APPOINTMENT_JSON
DEFINES += APPOINTMENT_PROTOBUFF

#DEFINES += APPOINTMENT_TYPE = APPOINTMENT_DATASTREAM

INCLUDEPATH += $$PWD
HEADERS += $$PWD/NetAppointments.h
SOURCES += $$PWD/NetAppointments.cpp \
    $$PWD/datastream_type/NetDataStream.cpp

contains(DEFINES, APPOINTMENT_DATASTREAM){
        INCLUDEPATH += $$PWD/datastream_type
        HEADERS += $$PWD/datastream_type/NetDataStream.h
}

contains(DEFINES, APPOINTMENT_JSON){
        INCLUDEPATH += $$PWD/json_type
        HEADERS += $$PWD/json_type/NetJson.h
}

contains(DEFINES, APPOINTMENT_PROTOBUFF){
        INCLUDEPATH += $$PWD/protobuff_type
        HEADERS += $$PWD/protobuff_type/NetProtobuff.h
}



