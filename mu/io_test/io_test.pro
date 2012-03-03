TEMPLATE = lib
CONFIG += static
CONFIG -= qt

HEADERS += \
    wistream_input_test.h \
    values.h \
    tests.h \
    source.h \
    source_result.h \
    single.h \
    routine.h \
    parser.h \
    parser_result.h \
    multiline_comment.h \
    lexer.h \
    lexer_result.h \
    istream_input_test.h \
    hex_code.h \
    full.h \
    extension4.h \
    extension3.h \
    extension2.h \
    extension1.h \
    extension.h \
    control.h \
    complex_identifier.h \
    builder.h \
    begin.h \
    analyzer.h \
    analyzer_result.h

SOURCES += \
    wistream_input_test.cpp \
    values.cpp \
    tests.cpp \
    source.cpp \
    source_result.cpp \
    single.cpp \
    routine.cpp \
    parser.cpp \
    parser_result.cpp \
    multiline_comment.cpp \
    lexer.cpp \
    lexer_result.cpp \
    istream_input_test.cpp \
    hex_code.cpp \
    full.cpp \
    extension4.cpp \
    extension3.cpp \
    extension2.cpp \
    extension1.cpp \
    extension.cpp \
    control.cpp \
    complex_identifier.cpp \
    builder.cpp \
    begin.cpp \
    analyzer.cpp \
    analyzer_result.cpp

INCLUDEPATH += \
    $(BASE)

QMAKE_CXXFLAGS += \
    -std=c++0x
