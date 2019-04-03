#-------------------------------------------------
#
# Project created by QtCreator 2019-03-19T05:03:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sysbro-startup-apps
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

TRANSLATIONS += translations/sysbro-startup-apps.ts \
                translations/sysbro-startup-apps_zh_CN.ts

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    listview.cpp \
    listmodel.cpp \
    autostartmanager.cpp \
    itemdelegate.cpp \
    createwindow.cpp \
    editdialog.cpp \
    desktopproperties.cpp

HEADERS += \
        mainwindow.h \
    listview.h \
    listmodel.h \
    autostartmanager.h \
    itemdelegate.h \
    createwindow.h \
    editdialog.h \
    desktopproperties.h

target.path = /usr/bin

translations.path = /usr/share/sysbro-startup-apps/translations
translations.files = $$PWD/translations/*.qm

INSTALLS += target translations

RESOURCES += \
    resources.qrc
