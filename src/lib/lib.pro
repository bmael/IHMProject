DEPENDPATH += $$PWD


! include( ../common.pri ) {
    error( Couldn't find the common.pri file! )
}

TEMPLATE = lib

HEADERS += pugixml_sources/pugiconfig.hpp \
           pugixml_sources/pugixml.hpp

SOURCES += pugixml_sources/pugixml.cpp


