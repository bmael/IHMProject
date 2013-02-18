#-------------------------------------------------
#
# Project created by QtCreator 2013-01-22T16:50:37
#
#-------------------------------------------------


TEMPLATE = subdirs
SUBDIRS = $$PWD/src/lib \
    $$PWD/src/ihm \
    $$PWD/src/Concept

$$PWD/src/Concept.depends = $$PWD/src/lib
$$PWD/src/Concept/Tools.depends = $$PWD/src/Concept/Manager
$$PWD/src/ihm/Tools.depends = $$PWD/src/lib
