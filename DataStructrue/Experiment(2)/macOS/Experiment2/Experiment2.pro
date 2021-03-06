#-------------------------------------------------
#
# Project created by QtCreator 2017-12-20T14:38:12
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Experiment2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
gethtmlfile.cpp \
CharString.cpp \
extractKeyWords.cpp \
UnicodeToGBK.cpp \
wordSegmentation.cpp \
    pageinfo.cpp \
    pagelink.cpp \
    inverteddocs.cpp \
    doclink.cpp \
    woogle.cpp \
    initpage.cpp \
    searchpage.cpp \
    detailedpage.cpp \
    mhash.cpp


HEADERS += \
        mainwindow.h \
gethtmlfile.h \
Link.h \
mAVL.h \
Stack.h \
UnicodeToGBK.h \
wordSegmentation.h \
CharString.h \
extractKeyWords.h \
    pageinfo.h \
    pagelink.h \
    inverteddocs.h \
    doclink.h \
    woogle.h \
    initpage.h \
    searchpage.h \
    detailedpage.h \
    mhash.h


FORMS += \
        mainwindow.ui
