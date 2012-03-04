TEMPLATE = lib
CONFIG += static
CONFIG -= qt
TARGET = mu_script

HEADERS += \
    values.operation.h \
    values.create.h \
    unit.operation.h \
    times.operation.h \
    string.node.h \
    string.extension.h \
    runtime.routine.h \
    runtime.reference.h \
    runtime.parameters.h \
    runtime.node.h \
    runtime.expression.h \
    runtime.context.h \
    runtime.constant.h \
    runtime.call.h \
    run.operation.h \
    print.operation.h \
    package.remove.h \
    package.node.h \
    package.get.h \
    package.get_recursive.h \
    package.create.h \
    package.create_from_cluster.h \
    package.add.h \
    operation.h \
    loads.operation.h \
    loadb.operation.h \
    load.operation.h \
    integer.subtract.h \
    integer.node.h \
    integer.extension.h \
    integer.equal.h \
    if_c.operation.h \
    identity.operation.h \
    fixed.h \
    extensions.node.h \
    extensions.merge.h \
    extensions.merge_package.h \
    extensions.merge_cluster.h \
    extensions.create.h \
    exec.operation.h \
    cluster.node.h \
    cluster.get_named.h \
    closure.single.h \
    closure.operation.h \
    closure.hole.h \
    closure.create.h \
    closure.create_single.h \
    closure.apply.h \
    chain.operation.h \
    bool_c.node.h \
    bool_c.equal.h \
    bool_c.create.h \
    astring.truncate.h \
    astring.node.h \
    astring.extension.h \
    ast.read_from_file.h \
    ast.merge.h \
    ast.extension.h \
    analyzer.operation.h

SOURCES += \
    values.operation.cpp \
    values.create.cpp \
    unit.operation.cpp \
    times.operation.cpp \
    string.node.cpp \
    string.extension.cpp \
    runtime.routine.cpp \
    runtime.reference.cpp \
    runtime.parameters.cpp \
    runtime.node.cpp \
    runtime.expression.cpp \
    runtime.context.cpp \
    runtime.constant.cpp \
    runtime.call.cpp \
    run.operation.cpp \
    print.operation.cpp \
    package.remove.cpp \
    package.node.cpp \
    package.get.cpp \
    package.get_recursive.cpp \
    package.create.cpp \
    package.create_from_cluster.cpp \
    package.add.cpp \
    operation.cpp \
    loads.operation.cpp \
    loadb.operation.cpp \
    load.operation.cpp \
    integer.subtract.cpp \
    integer.node.cpp \
    integer.extension.cpp \
    integer.equal.cpp \
    if_c.operation.cpp \
    identity.operation.cpp \
    fixed.cpp \
    extensions.node.cpp \
    extensions.merge.cpp \
    extensions.merge_package.cpp \
    extensions.merge_cluster.cpp \
    extensions.create.cpp \
    exec.operation.cpp \
    cluster.node.cpp \
    cluster.get_named.cpp \
    closure.single.cpp \
    closure.operation.cpp \
    closure.hole.cpp \
    closure.create.cpp \
    closure.create_single.cpp \
    closure.apply.cpp \
    chain.operation.cpp \
    bool_c.node.cpp \
    bool_c.equal.cpp \
    bool_c.create.cpp \
    astring.truncate.cpp \
    astring.node.cpp \
    astring.extension.cpp \
    ast.read_from_file.cpp \
    ast.merge.cpp \
    ast.extension.cpp \
    analyzer.operation.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x
