TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h \
    serverthreads.h

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread
