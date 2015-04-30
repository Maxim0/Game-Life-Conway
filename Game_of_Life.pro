TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game.cpp

HEADERS += \
    game.h

LIBS += -lglut -lGL -lGLU
