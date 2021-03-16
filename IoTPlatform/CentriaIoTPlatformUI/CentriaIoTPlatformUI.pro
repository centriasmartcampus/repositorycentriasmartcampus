QT += core
QT += gui
QT += network
QT += xml
QT += sql

CONFIG += c++14
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CentriaIoTPlatformUI
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    dialogcreatehierarchyitem.cpp \
    dialogcreateobjectlink.cpp \
        main.cpp \
        mainwindow.cpp \
    ../../Common/centriafastcgitcplistener.cpp \
    ../../Common/DTO/centriafastcgitcplistenerdto.cpp \
    DTO/centriawebservicedto.cpp \
    centriasqlconnection.cpp \
    DTO/centriasqlconnectiondto.cpp

HEADERS += \
    dialogcreatehierarchyitem.h \
    dialogcreateobjectlink.h \
        mainwindow.h \
    ../../Common/centriafastcgitcplistener.h \
    ../../Common/centriafastcgirequest.h \
    ../../Common/DTO/centriafastcgitcplistenerdto.h \
    DTO/centriawebservicedto.h \
    centriasqlconnection.h \
    DTO/centriasqlconnectiondto.h \
    Entities/sqlobject.h \
    Entities/sqlobjecthierarchy.h

FORMS += \
    dialogcreatehierarchyitem.ui \
    dialogcreateobjectlink.ui \
        mainwindow.ui

INCLUDEPATH += ../../SCInclude


DISTFILES += \
    config.ini

copyConfig.commands = $(COPY) $$shell_path($$PWD/config.ini) $$shell_path($$OUT_PWD/$$DESTDIR/config.ini)
first.depends += $(first) copyConfig
QMAKE_EXTRA_TARGETS += first copyConfig

