TEMPLATE = lib
CONFIG += dynamic
CONFIG -= qt
TARGET = mu_binary_test

SOURCES += \
    entry.cpp

INCLUDEPATH += \
    $(BASE) \
    $(BASE)/boost

QMAKE_CXXFLAGS += \
    -std=c++0x

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
