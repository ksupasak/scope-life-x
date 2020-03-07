#QT -= gui
QT += widgets core gui multimedia multimediawidgets serialport  webenginewidgets network sql

TEMPLATE = lib
DEFINES += SCOPELIFEGUI_LIBRARY

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customwebenginepage.cpp \
    scopelifegui.cpp \
    videocontroller.cpp \
    videosetting.cpp \
    webcontroller.cpp

HEADERS += \
    ScopeLifeGUI_global.h \
    customwebenginepage.h \
    scopelifegui.h \
    videocontroller.h \
    videosetting.h \
    webcontroller.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../ScopeLifeCore/release/ -lScopeLifeCore
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../ScopeLifeCore/debug/ -lScopeLifeCore
else:unix: LIBS += -L$$OUT_PWD/../ScopeLifeCore/ -lScopeLifeCore

INCLUDEPATH += $$PWD/../ScopeLifeCore
DEPENDPATH += $$PWD/../ScopeLifeCore

FORMS += \
    videocontroller.ui \
    videosetting.ui \
    webcontroller.ui

RESOURCES += \
    Resources.qrc
