#-------------------------------------------------
#
# Project created by QtCreator 2015-05-03T09:27:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = aubonlait
TEMPLATE = app
CONFIG += c++11


SOURCES += main.cpp\
        mainwindow.cpp \
    surveywizard.cpp \
    slavespinbox.cpp \
    slaveslider.cpp

HEADERS  += mainwindow.h \
    surveywizard.h \
    slavespinbox.h \
    slaveslider.h

FORMS    += mainwindow.ui \
    surveywizard.ui
