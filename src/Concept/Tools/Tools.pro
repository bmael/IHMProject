TEMPLATE = app
CONFIG += console
CONFIG -= qt

! include( ../../common.pri ) {
    error( Couldn't find the common.pri file! )
}

LIBS += ../../lib/liblib.a
LIBS += ../Manager/libManager.a

SOURCES += main.cpp \
    parser.cpp \
    sorting.cpp

HEADERS += \
    parser.h \
    sorting.h

