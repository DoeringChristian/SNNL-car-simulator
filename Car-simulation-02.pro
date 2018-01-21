TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    car.cpp \
    cube.cpp \
    matrixd.cpp \
    network.cpp \
    pnode.cpp \
    poligon.cpp \
    sensor.cpp \
    trainer.cpp \
    vector2d.cpp \
    vectord.cpp \
    world.cpp \
    line.cpp

DEFINES += SFML_STATIC

LIBS += -static

LIBS += -LC:/SFML-2.1/lib

INCLUDEPATH += C:/SFML-2.1/include
DEPENDPATH += C:/SFML-2.1/include

LIBS += -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lsfml-network-s-d -lsfml-audio-s-d

HEADERS += \
    car.h \
    cube.h \
    matrixd.h \
    network.h \
    pnode.h \
    poligon.h \
    sensor.h \
    simulation.h \
    trainer.h \
    vector2d.h \
    vectord.h \
    world.h \
    line.h
