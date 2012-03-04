TEMPLATE = lib
CONFIG += dynamic
CONFIG -= qt
TARGET = mu_llvm_binary

SOURCES += \
    entry.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost \
    $(BASE)/llvm/include

QMAKE_CXXFLAGS += \
    -std=c++0x

DEFINES += \
    __STDC_LIMIT_MACROS \
    __STDC_CONSTANT_MACROS

LIBS += -L$$OUT_PWD/../io/ -lmu_io
INCLUDEPATH += $$PWD/../io
DEPENDPATH += $$PWD/../io
PRE_TARGETDEPS += $$OUT_PWD/../io/libmu_io.a

LIBS += -L$$OUT_PWD/../core/ -lmu_core
INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
PRE_TARGETDEPS += $$OUT_PWD/../core/libmu_core.a

LIBS += -L$$OUT_PWD/../script/ -lmu_script
INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script
PRE_TARGETDEPS += $$OUT_PWD/../script/libmu_script.a

LIBS += -L$$OUT_PWD/../llvm_/ -lmu_llvm_
INCLUDEPATH += $$PWD/../llvm_
DEPENDPATH += $$PWD/../llvm_
PRE_TARGETDEPS += $$OUT_PWD/../llvm_/libmu_llvm_.a

LIBS += -L$$OUT_PWD/../script_io/ -lmu_script_io
INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io
PRE_TARGETDEPS += $$OUT_PWD/../script_io/libmu_script_io.a

LIBS += \
    -L$(BASE)/llvm/Debug/lib \
    -lLLVMCore \
    -lLLVMSupport \
    -lLLVMExecutionEngine \
    -lLLVMTarget \
    -lLLVMJIT \
    -lLLVMMC \
    -lLLVMCodeGen \
    -lLLVMAnalysis \
    -lLLVMTransformUtils \
    -lLLVMSelectionDAG \
    -lLLVMScalarOpts \
    -lLLVMAsmParser \
    -lLLVMLinker \
    -lLLVMX86AsmPrinter \
    -lLLVMX86CodeGen \
    -lLLVMX86Info \
    -lLLVMX86Desc \
    -lLLVMX86Utils \
    -lLLVMAsmPrinter \
    -lLLVMMCParser
