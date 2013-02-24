#-------------------------------------------------
#
# Project created by QtCreator 2013-02-23T11:22:54
#
#-------------------------------------------------

QT       += core gui

TARGET = imsvr_client
TEMPLATE = app

INCLUDEPATH += f:\code\boost_1_52_0

LIBS+= -LF:\code\boost_1_52_0\stage\lib\win32\vs10_0\ -llibboost_system-vc100-mt-gd-1_52 -llibboost_regex-vc100-mt-gd-1_52


SOURCES += main.cpp\
        mainwindow.cpp \
    LoginWindow.cpp \
    Client.cpp

HEADERS  += mainwindow.h \
    LoginWindow.h \
    Client.h

FORMS    += mainwindow.ui \
    logindialog.ui
