QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

versionAtMost(QT_VERSION, 6.0): CONFIG += c++17
versionAtLeast(QT_VERSION, 6.1): CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
DEFINES += QT_DISABLE_DEPRECATED_UP_TO=0x060800

SOURCES += \
    client.cpp \
    disconnectdialog.cpp \
    game.cpp \
    gui.cpp \
    main.cpp \
    muehle.cpp \
    networkmanager.cpp \
    server.cpp \
    serverdialog.cpp

HEADERS += \
    client.h \
    disconnectdialog.h \
    game.h \
    gamestate.h \
    gui.h \
    moveorientation.h \
    movestatus.h \
    muehle.h \
    nachrichtenformat.h \
    networkmanager.h \
    orientation.h \
    position.h \
    positionstate.h \
    removestatus.h \
    server.h \
    serverdialog.h \
    square.h \
    waitcornfirm.h

FORMS += \
    disconnectdialog.ui \
    gui.ui \
    muehle.ui \
    serverdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imageResources.qrc
