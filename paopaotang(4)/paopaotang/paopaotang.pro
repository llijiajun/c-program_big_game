#-------------------------------------------------
#
# Project created by QtCreator 2018-05-27T19:42:20
#
#-------------------------------------------------

QT       += core gui
QT      +=multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = paopaotang
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Player.cpp \
    Specs.cpp \
    world.cpp \
    Bomb.cpp \
    box.cpp \
    barrier.cpp \
    nonbarrier.cpp \
    under.cpp \
    pitfall.cpp \
    score.cpp

HEADERS  += mainwindow.h \
    Player.h \
    Specs.h \
    world.h \
    Bomb.h \
    box.h \
    barrier.h \
    nonbarrier.h \
    under.h \
    pitfall.h \
    score.h

FORMS    += mainwindow.ui
