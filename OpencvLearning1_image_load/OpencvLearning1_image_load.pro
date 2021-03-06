#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T11:02:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpencvLearning
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
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui

#INCLUDEPATH+=\
#            C:/opencv/opencv3_2/build/include\
#            C:/opencv/opencv3_2/build/include/opencv\
#            C:/opencv/opencv3_2/build/include/opencv2\

#LIBS+= C:/opencv/opencv3_2/build/x64/vc14/lib/opencv_world320d.lib\
#       C:/opencv/opencv3_2/build/x64/vc14/lib/opencv_world320.lib\

INCLUDEPATH += /opt/hmi_depends/opencv3.4.1/include \
               /opt/hmi_depends/opencv3.4.1/include/opencv \
               /opt/hmi_depends/opencv3.4.1/include/opencv2

LIBS += /opt/hmi_depends/opencv3.4.1/libs/libopencv_highgui.so \
        /opt/hmi_depends/opencv3.4.1/libs/libopencv_core.so    \
        /opt/hmi_depends/opencv3.4.1/libs/libopencv_imgproc.so \
        /opt/hmi_depends/opencv3.4.1/libs/libopencv_imgcodecs.so



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
