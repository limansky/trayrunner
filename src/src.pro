QT += widgets network

CONFIG += c++17

TARGET = trayrunner

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    logview.cpp \
    main.cpp \
    settingsdialog.cpp \
    settingsmanager.cpp \
    trayicon.cpp \
    watchdog.cpp

HEADERS += \
    logview.h \
    settingsdialog.h \
    settingsmanager.h \
    trayicon.h \
    watchdog.h

FORMS += \
    logview.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    trayrunner.qrc
