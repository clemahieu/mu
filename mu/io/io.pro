TEMPLATE = lib
CONFIG += console
CONFIG -= qt

SOURCES += \
    tokens.visitor.cpp \
    tokens.token.cpp \
    tokens.stream_end.cpp \
    tokens.right_square.cpp \
    tokens.parameters.cpp \
    tokens.left_square.cpp \
    tokens.identifier.cpp \
    tokens.divider.cpp \
    source.cpp \
    parser.values.cpp \
    parser.single.cpp \
    parser.full.cpp \
    parser.finished.cpp \
    parser.error.cpp \
    parser.cpp \
    parser.begin.cpp \
    lexer.wistream_input.cpp \
    lexer.token_vector.cpp \
    lexer.state.cpp \
    lexer.singleline_comment.cpp \
    lexer.multiline_comment.cpp \
    lexer.istream_input.cpp \
    lexer.identifier.cpp \
    lexer.hex_code.cpp \
    lexer.error.cpp \
    lexer.control.cpp \
    lexer.complex_identifier.cpp \
    lexer.character_stream.cpp \
    lexer.begin.cpp \
    builder.cpp \
    ast.visitor.cpp \
    ast.parameters.cpp \
    ast.node.cpp \
    ast.identifier.cpp \
    ast.expression.cpp \
    ast.end.cpp \
    ast.cluster.cpp \
    analyzer.routine.cpp \
    analyzer.resolver.cpp \
    analyzer.extensions.global.cpp \
    analyzer.extensions.extensions.cpp \
    analyzer.extensions.extension.cpp \
    analyzer.expression.cpp \
    analyzer.analyzer.cpp \
    lexer.lexer.cpp

HEADERS += \
    tokens.visitor.h \
    tokens.token.h \
    tokens.stream_end.h \
    tokens.right_square.h \
    tokens.parameters.h \
    tokens.left_square.h \
    tokens.identifier.h \
    tokens.divider.h \
    source.h \
    parser.values.h \
    parser.single.h \
    parser.parser.h \
    parser.full.h \
    parser.finished.h \
    parser.error.h \
    parser.begin.h \
    lexer.wistream_input.h \
    lexer.token_vector.h \
    lexer.state.h \
    lexer.singleline_comment.h \
    lexer.multiline_comment.h \
    lexer.istream_input.h \
    lexer.identifier.h \
    lexer.hex_code.h \
    lexer.h \
    lexer.error.h \
    lexer.control.h \
    lexer.complex_identifier.h \
    lexer.character_stream.h \
    lexer.begin.h \
    builder.h \
    ast.visitor.h \
    ast.parameters.h \
    ast.node.h \
    ast.identifier.h \
    ast.expression.h \
    ast.end.h \
    ast.cluster.h \
    analyzer.routine.h \
    analyzer.resolver.h \
    analyzer.extensions.global.h \
    analyzer.extensions.extensions.h \
    analyzer.extensions.extension.h \
    analyzer.expression.h \
    analyzer.analyzer.h \
    lexer.lexer.h

INCLUDEPATH += \
    $(BASE)

QMAKE_CXXFLAGS += \
    -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:symbian: LIBS += -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
