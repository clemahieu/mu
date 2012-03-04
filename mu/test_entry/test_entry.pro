TEMPLATE = app
CONFIG -= qt
TARGET = mu_test_entry

SOURCES += \
    main.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/llvm/include \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x

DEFINES += \
    __STDC_LIMIT_MACROS \
    __STDC_CONSTANT_MACROS

LIBS += -L$$OUT_PWD/../core_test/ -lmu_core_test
INCLUDEPATH += $$PWD/../core_test
DEPENDPATH += $$PWD/../core_test
PRE_TARGETDEPS += $$OUT_PWD/../core_test/libmu_core_test.a

LIBS += -L$$OUT_PWD/../io_test/ -lmu_io_test
INCLUDEPATH += $$PWD/../io_test
DEPENDPATH += $$PWD/../io_test
PRE_TARGETDEPS += $$OUT_PWD/../io_test/libmu_io_test.a

LIBS += -L$$OUT_PWD/../script_test/ -lmu_script_test
INCLUDEPATH += $$PWD/../script_test
DEPENDPATH += $$PWD/../script_test
PRE_TARGETDEPS += $$OUT_PWD/../script_test/libmu_script_test.a

LIBS += -L$$OUT_PWD/../script_io_test/ -lmu_script_io_test
INCLUDEPATH += $$PWD/../script_io_test
DEPENDPATH += $$PWD/../script_io_test
PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/libmu_script_io_test.a

LIBS += -L$$OUT_PWD/../llvm_test/ -lmu_llvm_test
INCLUDEPATH += $$PWD/../llvm_test
DEPENDPATH += $$PWD/../llvm_test
PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/libmu_llvm_test.a

LIBS += -L$$OUT_PWD/../repl_test/ -lmu_repl_test
INCLUDEPATH += $$PWD/../repl_test
DEPENDPATH += $$PWD/../repl_test
PRE_TARGETDEPS += $$OUT_PWD/../repl_test/libmu_repl_test.a

LIBS += -L$$OUT_PWD/../core/ -lmu_core
INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
PRE_TARGETDEPS += $$OUT_PWD/../core/libmu_core.a

LIBS += -L$$OUT_PWD/../io/ -lmu_io
INCLUDEPATH += $$PWD/../io
DEPENDPATH += $$PWD/../io
PRE_TARGETDEPS += $$OUT_PWD/../io/libmu_io.a

LIBS += -L$$OUT_PWD/../llvm_/ -lmu_llvm_
INCLUDEPATH += $$PWD/../llvm_
DEPENDPATH += $$PWD/../llvm_
PRE_TARGETDEPS += $$OUT_PWD/../llvm_/libmu_llvm_.a

LIBS += -L$$OUT_PWD/../repl/ -lmu_repl
INCLUDEPATH += $$PWD/../repl
DEPENDPATH += $$PWD/../repl
PRE_TARGETDEPS += $$OUT_PWD/../repl/libmu_repl.a

LIBS += -L$$OUT_PWD/../script/ -lmu_script
INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script
PRE_TARGETDEPS += $$OUT_PWD/../script/libmu_script.a

LIBS += -L$$OUT_PWD/../script_io/ -lmu_script_io
INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io
PRE_TARGETDEPS += $$OUT_PWD/../script_io/libmu_script_io.a

LIBS += \
    -L$(BASE)/boost/stage/lib \
    -lboost_filesystem \
    -lboost_system

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
