QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle
DEFINES += QT_DEPRECATED_WARNINGS

LIBS += \
    -lboost_program_options-mt \

LIBS += -L/mingw64/lib/

SOURCES += \
    main.cpp
