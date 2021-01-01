QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    codeeditor.cpp \
    grammar_analysis.cpp \
    highlighter.cpp \
    lexical_analysis.cpp \
    main.cpp \
    mainwindow.cpp \
    preprocess.cpp

HEADERS += \
    codeeditor.h \
    grammar_analysis.h \
    highlighter.h \
    include.h \
    lexical_analysis.h \
    mainwindow.h \
    preprocess.h \
    typedef.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
