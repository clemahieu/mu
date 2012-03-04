TEMPLATE = app
CONFIG -= qt

SOURCES += \
    main.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../repl/release/ -lrepl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../repl/debug/ -lrepl
else:symbian: LIBS += -lrepl
else:unix: LIBS += -L$$OUT_PWD/../repl/ -lrepl

INCLUDEPATH += $$PWD/../repl
DEPENDPATH += $$PWD/../repl

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/release/repl.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../repl/debug/repl.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../repl/librepl.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script_io/release/ -lscript_io
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script_io/debug/ -lscript_io
else:symbian: LIBS += -lscript_io
else:unix: LIBS += -L$$OUT_PWD/../script_io/ -lscript_io

INCLUDEPATH += $$PWD/../script_io
DEPENDPATH += $$PWD/../script_io

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/release/script_io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script_io/debug/script_io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script_io/libscript_io.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../io/release/ -lio
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../io/debug/ -lio
else:symbian: LIBS += -lio
else:unix: LIBS += -L$$OUT_PWD/../io/ -lio

INCLUDEPATH += $$PWD/../io
DEPENDPATH += $$PWD/../io

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/release/io.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../io/debug/io.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../io/libio.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:symbian: LIBS += -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/release/core.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../core/debug/core.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../core/libcore.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../script/release/ -lscript
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../script/debug/ -lscript
else:symbian: LIBS += -lscript
else:unix: LIBS += -L$$OUT_PWD/../script/ -lscript

INCLUDEPATH += $$PWD/../script
DEPENDPATH += $$PWD/../script

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/release/script.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../script/debug/script.lib
else:unix:!symbian: PRE_TARGETDEPS += $$OUT_PWD/../script/libscript.a

LIBS += \
    -L$(BASE)/boost/stage/lib \
    -lboost_filesystem \
    -lboost_system
