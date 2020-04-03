TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    kmp.cpp \
    ac_test.cpp

QMAKE_CXXFLAGS += -std=c++11

INCLUDEPATH += /usr/local/opencv4/include/opencv4
LIBS += -L/usr/local/opencv4/lib -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc

LIBS += -lpthread

HEADERS += \
    func.h \
    multi_thread.h \
    tree.h \
    kmp.h \
    ac_test.h
