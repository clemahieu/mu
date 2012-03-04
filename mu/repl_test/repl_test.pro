TEMPLATE = lib
CONFIG += static
CONFIG -= qt
TARGET = mu_repl_test

HEADERS += \
    tests.h \
    file_stream_test.h \
    api_test.h

SOURCES += \
    tests.cpp \
    file_stream_test.cpp \
    api_test.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x
