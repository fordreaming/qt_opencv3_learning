#-------------------------------------------------
#
# Project created by QtCreator 2020-10-28T10:11:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OptimalTemplateMatch
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

#algorithm lib + boost
INCLUDEPATH += /opt/hmi_depends/algorithm_depends/include
#opencv3.4.1
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include/opencv
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include/opencv2

#libs
LIBS += /opt/hmi_depends/opencv3.4.1/libs/libopencv*.so.3.4.1
LIBS += /opt/hmi_depends/algorithm_depends/libs/boost/libboost_*.so.1.58.0

LIBS += -L/opt/hmi_depends/algorithm_depends/libs/armadillo -larmadillo
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/glog -lglog
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/gflags -lgflags
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/mlpack -lmlpack
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/cholmod -lcholmod
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/cln/ -lcln
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/ginac/ -lginac
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/cgal
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/gomp -lgomp
LIBS += -L/opt/hmi_depends/algorithm_depends/libs/gsl/ -lgsl -lgslcblas

LIBS += -lCGAL_Core
LIBS += -lCGAL
LIBS += -lpthread
LIBS += -ldl

QMAKE_CXXFLAGS += -fopenmp
QMAKE_LFLAGS   += -fopenmp


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    imageproc.cpp \
    testcases.cpp \
    matchtemplate.cpp \
    findcircle.cpp

HEADERS += \
        mainwindow.h \
    imageproc.h \
    testcases.h \
    common.h \
    matchtemplate.h \
    findcircle.h

FORMS += \
        mainwindow.ui

DESTDIR += ../../qt_opencv3_learning_build/OptimalTemplateMatch
