#-------------------------------------------------
#
# Project created by QtCreator 2013-02-23T11:22:54
#
#-------------------------------------------------

QT       += core gui

TARGET = imsvr_client
TEMPLATE = app

INCLUDEPATH += $(HOME)/opt/include

LIBS+= -L$(HOME)/opt/lib -lboost_system -lboost_regex -lboost_thread


SOURCES += main.cpp\
        mainwindow.cpp \
    LoginWindow.cpp \
    Client.cpp

HEADERS  += mainwindow.h \
    LoginWindow.h \
    Client.h

FORMS    += mainwindow.ui \
    logindialog.ui
