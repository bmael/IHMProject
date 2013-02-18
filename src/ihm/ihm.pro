DEPENDPATH += $$PWD


#! include( ../common.pri ) {
#    error( Couldn't find the common.pri file! )
#}

include($$PWD/CustomWidgets/CustomWidgets.pri)
include($$PWD/TaskManager/TaskManager.pri)
include($$PWD/Tools/Tools.pri)

WARNINGS += -Wall

TEMPLATE = app

RESOURCES += \
    $$PWD/resources.qrc

TARGET = ../../TaskManager

LIBS += ../Concept/Manager/libManager.a
LIBS += ../lib/liblib.a
LIBS += ../Concept/Tools/libTools.a

OBJECTS_DIR = .cmp/ojb
MOC_DIR = .cmp/moc
RCC_DIR = .cmp/rcc
UI_DIR = .cmp/ui

TRANSLATIONS = ihm_en.ts

