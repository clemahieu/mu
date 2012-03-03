TEMPLATE = lib
CONFIG += static
CONFIG -= qt

HEADERS += \
    types.integer.h \
    tests.h \
    module.get_package.h \
    module.add_package.h \
    linker.link_modules.h \
    instructions.call.h \
    instruction_package.h \
    global_variable.create_set.h \
    function.create.h \
    function_type.create.h \
    extension.h \
    constant_string.extension.h \
    constant_string.create.h \
    ccall.operation.h \
    basic_block.insert.h \
    analyzer.operation.h

SOURCES += \
    types.integer.cpp \
    tests.cpp \
    module.get_package.cpp \
    module.add_package.cpp \
    linker.link_modules.cpp \
    instructions.call.cpp \
    instruction_package.cpp \
    global_variable.create_set.cpp \
    function.create.cpp \
    function_type.create.cpp \
    extension.cpp \
    constant_string.extension.cpp \
    constant_string.create.cpp \
    ccall.operation.cpp \
    basic_block.insert.cpp \
    analyzer.operation.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/llvm/include \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x

DEFINES += \
    __STDC_LIMIT_MACROS \
    __STDC_CONSTANT_MACROS
