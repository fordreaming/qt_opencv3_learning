TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pointsmatch.cpp \
    findoutercontours.cpp \
    matchtemplate.cpp

#opencv3.4.1
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include/opencv
INCLUDEPATH   += /opt/hmi_depends/opencv3.4.1/include/opencv2

#libs
LIBS += /opt/hmi_depends/opencv3.4.1/libs/libopencv*.so.3.4.1

HEADERS += \
    pointsmatch.h \
    findoutercontours.h \
    matchtemplate.h

DESTDIR += ../../qt_opencv3_learning_build/matchtemplate
