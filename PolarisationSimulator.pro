#-------------------------------------------------
#
# Project created by QtCreator 2019-11-20T21:54:45
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolarisationSimulator
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        ps_mainwindow.cpp \
    ps_element.cpp \
    ps_space.cpp \
    ps_mat.cpp \
    ps_vec.cpp \
    ps_stokescalc.cpp

HEADERS += \
        ps_mainwindow.h \
    ps_enum.h \
    ps_element.h \
    ps_space.h \
    ps_mat.h \
    ps_vec.h \
    ps_stokescalc.h

FORMS += \
        ps_mainwindow.ui \
    ps_stokescalc.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
