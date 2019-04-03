#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T21:31:04
#
#-------------------------------------------------

QT       += core gui svg concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysbro
TEMPLATE = app
CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

TRANSLATIONS += translations/sysbro.ts \
                translations/sysbro_zh_CN.ts

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    titlebar.cpp \
    utils.cpp \
    homepage.cpp \
    widgets/progressbar.cpp \
    widgets/monitorwidget.cpp \
    monitorthread.cpp \
    widgets/horizontalseparator.cpp \
    toolspage.cpp \
    widgets/dotwidget.cpp \
    toolsitemdelegate.cpp \
    toolslistmodel.cpp \
    toolsview.cpp\
    cleanerpage.cpp \
    scannedwidget.cpp \
    treewidget.cpp \
    treeitemdelegate.cpp \
    widgets/iconlabel.cpp \
    speeduppage.cpp \
    servicemodel.cpp \
    serviceitemdelegate.cpp \
    serviceview.cpp \
    widgets/trayicon.cpp

HEADERS += \
    mainwindow.h \
    titlebar.h \
    utils.h \
    homepage.h \
    widgets/progressbar.h \
    widgets/monitorwidget.h \
    monitorthread.h \
    widgets/horizontalseparator.h \
    toolspage.h \
    widgets/dotwidget.h \
    toolsitemdelegate.h \
    toolslistmodel.h \
    toolsview.h \
    cleanerpage.h \
    scannedwidget.h \
    treewidget.h \
    treeitemdelegate.h \
    widgets/iconlabel.h \
    speeduppage.h \
    servicemodel.h \
    serviceitemdelegate.h \
    serviceview.h \
    widgets/trayicon.h

RESOURCES += \
    resources.qrc

isEmpty(BINDIR):BINDIR=/usr/bin
isEmpty(APPDIR):APPDIR=/usr/share/applications
isEmpty(DSRDIR):DSRDIR=/usr/share/sysbro

target.path = $$INSTROOT$$BINDIR
desktop.path = $$INSTROOT$$APPDIR
desktop.files = $$PWD/../sysbro.desktop

icon.path = $$PREFIX/share/icons/hicolor/scalable/apps/
icon.files += $$PWD/resources/sysbro.svg \
              $$PWD/resources/sysbro-express.svg \
              $$PWD/resources/sysbro-file-shredder.svg \
              $$PWD/resources/sysbro-network-test.svg \
              $$PWD/resources/sysbro-startup-apps.svg

policy.path = /usr/share/polkit-1/actions
policy.files = com.sysbro.pkexec.delete-files.policy

translations.path = /usr/share/sysbro/translations
translations.files = $$PWD/translations/*.qm

INSTALLS += target desktop icon policy translations

DISTFILES += \
    resources/sysbro-network-test.svg \
    resources/sysbro-express.svg \
    resources/sysbro-startup-apps.svg
