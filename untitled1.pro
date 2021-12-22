QT       += core gui
QT       += axcontainer
QT       +=network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    datastream.cpp \
    main.cpp \
    mainwindow.cpp \
    readexceldata.cpp \
    tripletriadcards.cpp

HEADERS += \
    datastream.h \
    mainwindow.h \
    readexceldata.h \
    tripletriadcards.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ff14wiki.py \
    tttt.py


win32: LIBS += -LC:/Users/d4127/AppData/Local/Programs/Python/Python38/libs/ -lpython38

INCLUDEPATH += C:/Users/d4127/AppData/Local/Programs/Python/Python38/include
DEPENDPATH += C:/Users/d4127/AppData/Local/Programs/Python/Python38/include

win32:!win32-g++: PRE_TARGETDEPS += C:/Users/d4127/AppData/Local/Programs/Python/Python38/libs/python38.lib
#else:win32-g++: PRE_TARGETDEPS += C:/Users/d4127/AppData/Local/Programs/Python/Python38/libs/libpython38.a
