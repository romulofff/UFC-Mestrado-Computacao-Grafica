#-------------------------------------------------
#
# Project created by QtCreator 2013-12-25T01:54:27
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SceneEditor
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR     =   bin/debug
    OBJECTS_DIR =   obj/debug
} else {
    DESTDIR     =   bin/release
    OBJECTS_DIR =   obj/release
}

unix {
    LIBS +=  -lm -lGL -lGLU
}

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
    res/scene/Camera.cpp \
    res/scene/LightSource.cpp \
    res/scene/GLWidget.cpp \
    src/objects/Object.cpp \
    src/objects/Material.cpp \
    src/primitives/Vertex.cpp \
    src/primitives/Vector.cpp \
    src/primitives/Point.cpp \
    src/primitives/Face.cpp \
    src/primitives/AffineSpace.cpp

HEADERS  += \
    res/layout/mainwindow.h \
    res/scene/LightSource.h \
    res/scene/GLWidget.h \
    res/scene/Camera.h \
    src/objects/Object.h \
    src/objects/Material.h \
    src/primitives/Vertex.h \
    src/primitives/Vector.h \
    src/primitives/Point.h \
    src/primitives/Face.h \
    src/primitives/AffineSpace.h \

FORMS    += \
    res/layout/mainwindow.ui
