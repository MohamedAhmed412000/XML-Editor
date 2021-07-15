#-------------------------------------------------
#
# Project created by QtCreator 2021-07-10T22:33:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Text_Editor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    xmlsyntaxhighlighter.cpp \
    compress.cpp \
    Tree.cpp \
    XML_Data.cpp \
    Helper_Functions.cpp \
    substring.cpp \
    format.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    xmlsyntaxhighlighter.h \
    compress.h \
    Headers.h \
    Tree.h \
    XML_Data.h \
    Helper_Functions.h \
    substring.h \
    format.h

FORMS    += mainwindow.ui \
    finddialog.ui

RESOURCES += \
    resources.qrc
