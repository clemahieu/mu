TEMPLATE = app
CONFIG -= qt
CONFIG += console
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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core_test/release/ -lmu_core_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core_test/debug/ -lmu_core_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../core_test/ -lmu_core_test
INCLUDEPATH += $$PWD/../core_test
DEPENDPATH += $$PWD/../core_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core_test/release/mu_core_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core_test/debug/mu_core_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../core_test/libmu_core_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../io_test/release/ -lmu_io_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../io_test/debug/ -lmu_io_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../io_test/ -lmu_io_test
INCLUDEPATH += $$PWD/../io_test
DEPENDPATH += $$PWD/../io_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io_test/release/mu_io_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io_test/debug/mu_io_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../io_test/libmu_io_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_test/release/ -lmu_script_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_test/debug/ -lmu_script_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../script_test/ -lmu_script_test
INCLUDEPATH += $$PWD/../script_test
DEPENDPATH += $$PWD/../script_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_test/release/mu_script_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_test/debug/mu_script_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_test/libmu_script_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io_test/release/ -lmu_script_io_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io_test/debug/ -lmu_script_io_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../script_io_test/ -lmu_script_io_test
INCLUDEPATH += $$PWD/../script_io_test
DEPENDPATH += $$PWD/../script_io_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/release/mu_script_io_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/debug/mu_script_io_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/libmu_script_io_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../llvm_test/release/ -lmu_llvm_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../llvm_test/debug/ -lmu_llvm_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../llvm_test/ -lmu_llvm_test
INCLUDEPATH += $$PWD/../llvm_test
DEPENDPATH += $$PWD/../llvm_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/release/mu_llvm_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/debug/mu_llvm_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/libmu_llvm_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../repl_test/release/ -lmu_repl_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../repl_test/debug/ -lmu_repl_test
else:unix:!symbian: LIBS += -L$$OUT_PWD/../repl_test/ -lmu_repl_test
INCLUDEPATH += $$PWD/../repl_test
DEPENDPATH += $$PWD/../repl_test
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl_test/release/mu_repl_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl_test/debug/mu_repl_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../repl_test/libmu_repl_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lmu_core
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lmu_core
else:unix:!symbian: LIBS += -L$$OUT_PWD/../core/ -lmu_core
INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/mu_core.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/mu_core.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../core/libmu_core.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../io/release/ -lmu_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../io/debug/ -lmu_io
else:unix:!symbian: LIBS += -L$$OUT_PWD/../io/ -lmu_io
INCLUDEPATH += $$PWD/../io
DEPENDPATH += $$PWD/../io
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/release/mu_io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/debug/mu_io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../io/libmu_io.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../llvm_/release/ -lmu_llvm_
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../llvm_/debug/ -lmu_llvm_
else:unix:!symbian: LIBS += -L$$OUT_PWD/../llvm_/ -lmu_llvm_
INCLUDEPATH += $$PWD/../llvm_
DEPENDPATH += $$PWD/../llvm_
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_/release/mu_llvm_.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_/debug/mu_llvm_.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../llvm_/libmu_llvm_.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../repl/release/ -lmu_repl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../repl/debug/ -lmu_repl
else:unix:!symbian: LIBS += -L$$OUT_PWD/../repl/ -lmu_repl
INCLUDEPATH += $$PWD/../repl
DEPENDPATH += $$PWD/../repl
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/release/mu_repl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/debug/mu_repl.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../repl/libmu_repl.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script/release/ -lmu_script
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script/debug/ -lmu_script
else:unix:!symbian: LIBS += -L$$OUT_PWD/../script/ -lmu_script
INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/release/mu_script.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/debug/mu_script.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script/libmu_script.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io/release/ -lmu_script_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io/debug/ -lmu_script_io
else:unix:!symbian: LIBS += -L$$OUT_PWD/../script_io/ -lmu_script_io
INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io
win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/release/mu_script_io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/debug/mu_script_io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io/libmu_script_io.a

win32::CONFIG(release, debug|release): LIBS += \
    -L$(BASE)/boost/stage/lib/ -llibboost_filesystem-vc100-mt-1_47 \
    -L$(BASE)/boost/stage/lib/ -llibboost_system-vc100-mt-1_47
else:win32:CONFIG(debug, debug|release): LIBS += \
    -L$(BASE)/boost/stage/lib/ -llibboost_filesystem-vc100-mt-gd-1_47 \
    -L$(BASE)/boost/stage/lib/ -llibboost_system-vc100-mt-gd-1_47
else:unix:!symbian: LIBS += \
    -L$(BASE)/boost/stage/lib \
    -lboost_filesystem \
    -lboost_system

win32::CONFIG(release, debug|release): LIBS += \
    -L$(BASE)/llvm/lib/Release -lLLVMCore \
    -L$(BASE)/llvm/lib/Release -lLLVMSupport \
    -L$(BASE)/llvm/lib/Release -lLLVMExecutionEngine \
    -L$(BASE)/llvm/lib/Release -lLLVMTarget \
    -L$(BASE)/llvm/lib/Release -lLLVMJIT \
    -L$(BASE)/llvm/lib/Release -lLLVMMC \
    -L$(BASE)/llvm/lib/Release -lLLVMCodeGen \
    -L$(BASE)/llvm/lib/Release -lLLVMAnalysis \
    -L$(BASE)/llvm/lib/Release -lLLVMTransformUtils \
    -L$(BASE)/llvm/lib/Release -lLLVMSelectionDAG \
    -L$(BASE)/llvm/lib/Release -lLLVMScalarOpts \
    -L$(BASE)/llvm/lib/Release -lLLVMAsmParser \
    -L$(BASE)/llvm/lib/Release -lLLVMLinker \
    -L$(BASE)/llvm/lib/Release -lLLVMX86AsmPrinter \
    -L$(BASE)/llvm/lib/Release -lLLVMX86CodeGen \
    -L$(BASE)/llvm/lib/Release -lLLVMX86Info \
    -L$(BASE)/llvm/lib/Release -lLLVMX86Desc \
    -L$(BASE)/llvm/lib/Release -lLLVMX86Utils \
    -L$(BASE)/llvm/lib/Release -lLLVMAsmPrinter \
    -L$(BASE)/llvm/lib/Release -lLLVMMCParser
else:win32::CONFIG(debug, debug|release): LIBS += \
    -L$(BASE)/llvm/lib/Debug -lLLVMCore \
    -L$(BASE)/llvm/lib/Debug -lLLVMSupport \
    -L$(BASE)/llvm/lib/Debug -lLLVMExecutionEngine \
    -L$(BASE)/llvm/lib/Debug -lLLVMTarget \
    -L$(BASE)/llvm/lib/Debug -lLLVMJIT \
    -L$(BASE)/llvm/lib/Debug -lLLVMMC \
    -L$(BASE)/llvm/lib/Debug -lLLVMCodeGen \
    -L$(BASE)/llvm/lib/Debug -lLLVMAnalysis \
    -L$(BASE)/llvm/lib/Debug -lLLVMTransformUtils \
    -L$(BASE)/llvm/lib/Debug -lLLVMSelectionDAG \
    -L$(BASE)/llvm/lib/Debug -lLLVMScalarOpts \
    -L$(BASE)/llvm/lib/Debug -lLLVMAsmParser \
    -L$(BASE)/llvm/lib/Debug -lLLVMLinker \
    -L$(BASE)/llvm/lib/Debug -lLLVMX86AsmPrinter \
    -L$(BASE)/llvm/lib/Debug -lLLVMX86CodeGen \
    -L$(BASE)/llvm/lib/Debug -lLLVMX86Info \
    -L$(BASE)/llvm/lib/Debug -lLLVMX86Desc \
    -L$(BASE)/llvm/lib/Debug -lLLVMX86Utils \
    -L$(BASE)/llvm/lib/Debug -lLLVMAsmPrinter \
    -L$(BASE)/llvm/lib/Debug -lLLVMMCParser
else:unix:!symbian: LIBS += \
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
