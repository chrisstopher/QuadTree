TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    QuadTree.cpp \
    Entity.cpp \
    Rectangle.cpp \
    Vec2f.cpp

HEADERS += \
    QuadTree.h \
    Entity.h \
    Rectangle.h \
    Vec2f.h
