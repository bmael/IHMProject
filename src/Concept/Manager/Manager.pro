TEMPLATE = app
CONFIG += console
CONFIG -= qt

! include( ../../common.pri ) {
    error( Couldn't find the common.pri file! )
}

SOURCES += main.cpp \
    task.cpp \
    tasklist.cpp

HEADERS += \
    taskcomponent.h \
    task.h \
    tasklist.h

