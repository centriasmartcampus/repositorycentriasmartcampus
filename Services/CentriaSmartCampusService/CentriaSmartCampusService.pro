QT += core
QT += gui
QT += network
QT += xml

CONFIG += c++14
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CentriaSmartCampusService
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    scservice.cpp \
    DTO/scservicedto.cpp \
    sctcplistener.cpp \
    DTO/sctcplistenerdto.cpp

HEADERS += \
        mainwindow.h \
    scservice.h \
    DTO/scservicedto.h \
    sctcplistener.h \
    DTO/sctcplistenerdto.h \
    scfastcgirequest.h

INCLUDEPATH += ../../SCInclude

FORMS += \
        mainwindow.ui

DISTFILES += \
    config.ini

copyConfig.commands = $(COPY) $$shell_path($$PWD/config.ini) $$shell_path($$OUT_PWD/$$DESTDIR/config.ini)
first.depends += $(first) copyConfig
QMAKE_EXTRA_TARGETS += first copyConfig
