TEMPLATE = lib
CONFIG += console
CONFIG -= qt

SOURCES += \
    visitor.cpp \
    tests.cpp \
    test_visitor.cpp \
    segment.cpp \
    order.cpp \
    list.cpp \
    filesystem_test.cpp \
    directory_iterator_test.cpp \
    apply.cpp

HEADERS += \
    visitor.h \
    tests.h \
    test_visitor.h \
    segment.h \
    order.h \
    list.h \
    filesystem_test.h \
    directory_iterator_test.h \
    apply.h

INCLUDEPATH += \
    $(BASE)

QMAKE_CXXFLAGS += \
    -std=c++0x

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../core/release/ -lcore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../core/debug/ -lcore
else:symbian: LIBS += -lcore
else:unix: LIBS += -L$$OUT_PWD/../core/ -lcore

INCLUDEPATH += $$PWD/../core
DEPENDPATH += $$PWD/../core

LIBS += \
    -L$(BASE)/boost/stage/lib \
    -lboost_filesystem \
    -lboost_system
