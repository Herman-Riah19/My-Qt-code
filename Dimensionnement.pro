#-------------------------------------------------
#
# Project created by QtCreator 2020-02-24T11:10:15
#
#-------------------------------------------------

QT       += sql core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
requires (qtConfig (tableview))

TARGET = Dimensionnement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        capacitedownlink.cpp \
        capaciteenodeb.cpp \
        capaciteuplink.cpp \
        dialognewproject.cpp \
        dimensionnementcapacitewidget.cpp \
        dimensionnementcouverture.cpp \
        main.cpp \
        mainwindow.cpp \
        maplclass.cpp \
        propagationclass.cpp \
        resultatwidget.cpp \
        tablemodel.cpp

HEADERS += \
        capacitedownlink.h \
        capaciteenodeb.h \
        capaciteuplink.h \
        dialognewproject.h \
        dimensionnementcapacitewidget.h \
        dimensionnementcouverture.h \
        mainwindow.h \
        maplclass.h \
        propagationclass.h \
        resultatwidget.h \
        tablemodel.h

FORMS += \
        dialognewproject.ui \
        dimensionnementcapacitewidget.ui \
        dimensionnementcouverture.ui \
        mainwindow.ui \
        resultatwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

DISTFILES +=
