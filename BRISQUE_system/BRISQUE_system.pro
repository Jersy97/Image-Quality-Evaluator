#-------------------------------------------------
#
# Project created by QtCreator 2019-04-19T14:26:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BRISQUE_system
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    brisque.cpp \
    computescore.cpp \
    svm.cpp

HEADERS  += mainwindow.h \
    brisque.h \
    svm.h

FORMS    += mainwindow.ui


INCLUDEPATH+=D:/Qt/opencvfiles/include \
D:/Qt/opencvfiles/include/opencv \
D:/Qt/opencvfiles/include/opencv2

LIBS += D:/Qt/opencvfiles/bin/libopencv_*.dll


