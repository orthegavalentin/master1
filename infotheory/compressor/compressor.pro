TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    compressor.cpp \
    utils.cpp \
    decompressor.cpp

HEADERS += \
    compressor.h \
    utils.h \
    decompressor.h

QMAKE_CXXFLAGS += -std=c++11
