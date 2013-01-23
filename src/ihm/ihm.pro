DEPENDPATH += $$PWD


! include( ../common.pri ) {
    error( Couldn't find the common.pri file! )
}

include($$PWD/CustomWidgets/CustomWidgets.pri)
include($$PWD/TaskManager/TaskManager.pri)

WARNINGS += -Wall

TEMPLATE = app

RESOURCES += \
    $$PWD/resources.qrc

TARGET = ../../TaskManager



