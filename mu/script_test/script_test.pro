TEMPLATE = lib
CONFIG += static
CONFIG -= qt

HEADERS += \
    times.operation.h \
    tests.h \
    string.extension.h \
    routine.h \
    reference.h \
    package.get.h \
    package.get_recursive.h \
    package.create.h \
    loads.operation.h \
    loadb.operation.h \
    integer.equal.h \
    expression.h \
    constant.h \
    closure.single.h \
    closure.operation.h \
    closure.apply.h \
    chain.ten_count.h \
    chain.operation.h \
    call.h \
    ast.extension.h \
    analyzer.operation.h

SOURCES += \
    times.operation.cpp \
    tests.cpp \
    string.extension.cpp \
    routine.cpp \
    reference.cpp \
    package.get.cpp \
    package.get_recursive.cpp \
    package.create.cpp \
    loads.operation.cpp \
    loadb.operation.cpp \
    integer.equal.cpp \
    expression.cpp \
    constant.cpp \
    closure.single.cpp \
    closure.operation.cpp \
    closure.apply.cpp \
    chain.ten_count.cpp \
    chain.operation.cpp \
    call.cpp \
    ast.extension.cpp \
    analyzer.operation.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x
