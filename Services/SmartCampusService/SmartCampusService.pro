QT -= gui
QT += core
QT += network


CONFIG += c++14
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        ../../Common/DTO/centriafastcgitcplistenerdto.cpp \
        ../../Common/centriafastcgitcplistener.cpp \
        ../../Common/centriahttpsclient.cpp \
        DTO/centriascplatformclientdto.cpp \
        DTO/centriascservicedto.cpp \
        centriascplatformclient.cpp \
        centriascservice.cpp \
        main.cpp

INCLUDEPATH += ../../SCInclude

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    config.ini

copyConfig.commands = $(COPY) $$shell_path($$PWD/config.ini) $$shell_path($$OUT_PWD/$$DESTDIR/config.ini)
first.depends += $(first) copyConfig
QMAKE_EXTRA_TARGETS += first copyConfig

HEADERS += \
    ../../Common/DTO/centriafastcgitcplistenerdto.h \
    ../../Common/centriafastcgirequest.h \
    ../../Common/centriafastcgitcplistener.h \
    ../../Common/centriahttpsclient.h \
    DTO/centriascplatformclientdto.h \
    DTO/centriascservicedto.h \
    centriascplatformclient.h \
    centriascservice.h
