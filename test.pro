#TEMPLATE = app
#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    src/main.cpp \
    src/kmp.cpp \
    src/ac_tree.cpp

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += /usr/local/opencv4/include/opencv4
LIBS += -L/usr/local/opencv4/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

LIBS += -lpthread

HEADERS += \
    src/func.h \
    src/multi_thread.h \
    src/tree.h \
    src/kmp.h \
    src/ac_test.h \
    src/ac_tree.h \
    src/temp.h \
    src/biginteger.h \
    src/test_shared_ptr.h
