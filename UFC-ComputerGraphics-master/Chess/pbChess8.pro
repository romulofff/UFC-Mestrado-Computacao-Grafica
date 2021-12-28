#-------------------------------------------------
#
# Project created by QtCreator 2013-12-07T04:41:40
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pbChess8
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR     =   bin/debug
    OBJECTS_DIR =   obj/debug
} else {
    DESTDIR     =   bin/release
    OBJECTS_DIR =   obj/release
}

LIBS	+=  -lm -lGL -lGLU

UI_DIR  =   temp
RCC_DIR =   temp
MOC_DIR =   temp

INCLUDEPATH += \
    .res res/layout \
    .res res/scene \
    .src src/objects \
    .src src/primitives

SOURCES += \
    res/layout/mainwindow.cpp \
    res/layout/main.cpp \
    res/scene/PbCamera.cpp \
    src/primitives/PbVector.cpp \
    src/primitives/PbPoint.cpp \
    src/primitives/PbVertex.cpp \
    src/primitives/PbFace.cpp \
    src/primitives/PbAffineSpace.cpp \
    res/scene/PbLightSource.cpp \
    src/objects/PbObject.cpp \
    src/objects/PbMaterial.cpp \
    res/scene/PbGLWidget.cpp

HEADERS  += \
    res/layout/mainwindow.h \
    res/scene/PbCamera.h \
    src/primitives/PbVector.h \
    src/primitives/PbPoint.h \
    src/primitives/PbVertex.h \
    src/primitives/PbFace.h \
    src/primitives/PbAffineSpace.h \
    res/scene/PbLightSource.h \
    src/objects/PbObject.h \
    src/objects/PbMaterial.h \
    res/scene/PbGLWidget.h

FORMS    += \
    res/layout/mainwindow.ui
