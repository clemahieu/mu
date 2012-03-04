TEMPLATE = app
CONFIG -= qt

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core_test/release/ -lcore_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core_test/debug/ -lcore_test
else:symbian: LIBS += -lcore_test
else:unix: LIBS += -L$$OUT_PWD/../core_test/ -lcore_test

INCLUDEPATH += $$PWD/../core_test
DEPENDPATH += $$PWD/../core_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core_test/release/core_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core_test/debug/core_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../core_test/libcore_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../io_test/release/ -lio_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../io_test/debug/ -lio_test
else:symbian: LIBS += -lio_test
else:unix: LIBS += -L$$OUT_PWD/../io_test/ -lio_test

INCLUDEPATH += $$PWD/../io_test
DEPENDPATH += $$PWD/../io_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io_test/release/io_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io_test/debug/io_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../io_test/libio_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_test/release/ -lscript_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_test/debug/ -lscript_test
else:symbian: LIBS += -lscript_test
else:unix: LIBS += -L$$OUT_PWD/../script_test/ -lscript_test

INCLUDEPATH += $$PWD/../script_test
DEPENDPATH += $$PWD/../script_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_test/release/script_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_test/debug/script_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_test/libscript_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io_test/release/ -lscript_io_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io_test/debug/ -lscript_io_test
else:symbian: LIBS += -lscript_io_test
else:unix: LIBS += -L$$OUT_PWD/../script_io_test/ -lscript_io_test

INCLUDEPATH += $$PWD/../script_io_test
DEPENDPATH += $$PWD/../script_io_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/release/script_io_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/debug/script_io_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io_test/libscript_io_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../llvm_test/release/ -lllvm_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../llvm_test/debug/ -lllvm_test
else:symbian: LIBS += -lllvm_test
else:unix: LIBS += -L$$OUT_PWD/../llvm_test/ -lllvm_test

INCLUDEPATH += $$PWD/../llvm_test
DEPENDPATH += $$PWD/../llvm_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/release/llvm_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/debug/llvm_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../llvm_test/libllvm_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../repl_test/release/ -lrepl_test
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../repl_test/debug/ -lrepl_test
else:symbian: LIBS += -lrepl_test
else:unix: LIBS += -L$$OUT_PWD/../repl_test/ -lrepl_test

INCLUDEPATH += $$PWD/../repl_test
DEPENDPATH += $$PWD/../repl_test

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl_test/release/repl_test.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl_test/debug/repl_test.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../repl_test/librepl_test.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:symbian: LIBS += -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/core.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/core.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../io/release/ -lio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../io/debug/ -lio
else:symbian: LIBS += -lio
else:unix: LIBS += -L$$OUT_PWD/../io/ -lio

INCLUDEPATH += $$PWD/../io
DEPENDPATH += $$PWD/../io

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/release/io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/debug/io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../io/libio.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../llvm_/release/ -lllvm_
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../llvm_/debug/ -lllvm_
else:symbian: LIBS += -lllvm_
else:unix: LIBS += -L$$OUT_PWD/../llvm_/ -lllvm_

INCLUDEPATH += $$PWD/../llvm_
DEPENDPATH += $$PWD/../llvm_

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_/release/llvm_.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../llvm_/debug/llvm_.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../llvm_/libllvm_.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../repl/release/ -lrepl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../repl/debug/ -lrepl
else:symbian: LIBS += -lrepl
else:unix: LIBS += -L$$OUT_PWD/../repl/ -lrepl

INCLUDEPATH += $$PWD/../repl
DEPENDPATH += $$PWD/../repl

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/release/repl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/debug/repl.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../repl/librepl.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script/release/ -lscript
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script/debug/ -lscript
else:symbian: LIBS += -lscript
else:unix: LIBS += -L$$OUT_PWD/../script/ -lscript

INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/release/script.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/debug/script.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script/libscript.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io/release/ -lscript_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io/debug/ -lscript_io
else:symbian: LIBS += -lscript_io
else:unix: LIBS += -L$$OUT_PWD/../script_io/ -lscript_io

INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/release/script_io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/debug/script_io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io/libscript_io.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io/release/ -lscript_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io/debug/ -lscript_io
else:symbian: LIBS += -lscript_io
else:unix: LIBS += -L$$OUT_PWD/../script_io/ -lscript_io

INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/release/script_io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/debug/script_io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io/libscript_io.a

LIBS += \
    -L$(BASE)/boost/stage/lib \
    -lboost_filesystem \
    -lboost_system
