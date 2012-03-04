TEMPLATE = lib
CONFIG += static
CONFIG -= qt

HEADERS += \
    repl.h \
    quit.operation.h \
    file_stream.h \
    data_stream.h \
    cli_stream.h

SOURCES += \
    repl.cpp \
    quit.operation.cpp \
    file_stream.cpp \
    data_stream.cpp \
    cli_stream.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x
