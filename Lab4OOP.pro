#-------------------------------------------------
#
# Project created by QtCreator 2016-03-22T02:31:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab4OOP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ccircle.cpp \
    editor.cpp \
    state.cpp \
    cshape.cpp \
    crect.cpp \
    cgroup.cpp \
    cnpolygon.cpp

HEADERS  += mainwindow.h \
    ccircle.h \
    editor.h \
    state.h \
    ../lab3oop/emptyiterator.h \
    ../lab3oop/isaveable.h \
    ../lab3oop/iterator.h \
    ../lab3oop/slstorage.h \
    cshape.h \
    crect.h \
    cgroup.h \
    cnpolygon.h

FORMS    += mainwindow.ui

DISTFILES += \
    storage.txt \
    .gitignore \
    TODO.txt \
    LR.doc
