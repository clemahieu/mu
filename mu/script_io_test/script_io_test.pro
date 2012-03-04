TEMPLATE = lib
CONFIG += static
CONFIG -= qt
TARGET = mu_script_io_test

HEADERS += \
    tests.h \
    synthesizer.h \
    routine.h \
    lambda.h \
    call.h \
    builder.h

SOURCES += \
    tests.cpp \
    synthesizer.cpp \
    routine.cpp \
    lambda.cpp \
    call.cpp \
    builder.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x
