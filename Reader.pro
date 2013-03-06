#-------------------------------------------------
#
# Project created by QtCreator 2013-03-03T13:00:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Reader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    resultwindow.cpp

HEADERS  += mainwindow.h \
    resultwindow.h

FORMS    += mainwindow.ui \
    resultwindow.ui

RC_FILE = resource.rc

QMAKE_LFLAGS += -static-libgcc
