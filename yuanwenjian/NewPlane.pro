QT       += core gui
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    helpscene.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    media.cpp \
    myplane.cpp \
    paihangbang.cpp \
    restartscene.cpp \
    startbutton.cpp \
    startscene.cpp \
    middleplane.cpp \
    smallplane.cpp \
    baseplane.cpp \
    leftbullet.cpp \
    rightbullet.cpp \
    lianbiao.cpp \

HEADERS += \
    bullet.h \
    config.h \
    helpscene.h \
    mainscene.h \
    map.h \
    media.h \
    myplane.h \
    paihangbang.h \
    restartscene.h \
    startbutton.h \
    startscene.h \
    middleplane.h \
    smallplane.h \
    baseplane.h \
    leftbullet.h \
    rightbullet.h \
    lianbiao.h \

FORMS += \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES +=
