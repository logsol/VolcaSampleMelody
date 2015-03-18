#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T20:17:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VolcaSampleMelody
TEMPLATE = app


SOURCES += main.cpp\
    RtMidi.cpp \
    MainWindow.cpp

HEADERS  += \
    RtMidi.h \
    MainWindow.h

FORMS    += \
    MainWindow.ui

RESOURCES +=

DEFINES += __MACOSX_CORE__

DISTFILES +=

mac: LIBS += -F$$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/ -framework CoreAudio

INCLUDEPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks
DEPENDPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks

mac: LIBS += -F$$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/ -framework CoreMIDI

INCLUDEPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks
DEPENDPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks

mac: LIBS += -F$$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks/ -framework CoreFoundation

INCLUDEPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks
DEPENDPATH += $$PWD/../../../../../../Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk/System/Library/Frameworks
