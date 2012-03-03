TEMPLATE = lib
CONFIG += static
CONFIG -= qt

SOURCES += main.cpp \
    routine.cpp \
    reference.cpp \
    position.cpp \
    parameters.cpp \
    order.cpp \
    node.cpp \
    expression.cpp \
    errors.string_error.cpp \
    errors.error.cpp \
    errors.error_target.cpp \
    errors.error_list.cpp \
    errors.error_context.cpp \
    context.cpp \
    cluster.cpp \
    apply.cpp

HEADERS += \
    visitor.h \
    segment.h \
    routine.h \
    reference.h \
    position.h \
    parameters.h \
    order.h \
    node.h \
    expression.h \
    errors.string_error.h \
    errors.error.h \
    errors.error_target.h \
    errors.error_list.h \
    errors.error_context.h \
    context.h \
    cluster.h \
    apply.h

INCLUDEPATH += \
    $(BASE)

QMAKE_CXXFLAGS += \
    -std=c++0x
