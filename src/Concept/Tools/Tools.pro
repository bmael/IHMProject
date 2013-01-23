TEMPLATE = app
CONFIG += console
CONFIG -= qt

! include( ../../common.pri ) {
    error( Couldn't find the common.pri file! )
}

SOURCES += main.cpp \
    parser.cpp

HEADERS += \
    parser.h

