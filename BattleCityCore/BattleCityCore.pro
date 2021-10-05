QT += gui core widgets

TEMPLATE = lib
DEFINES += BATTLECITYCORE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GraphicsSceneObjects/GameObject.cpp \
    GraphicsSceneObjects/staticbody.cpp \
    GraphicsScenes/gamescene.cpp \
    GraphicsScenes/menuscene.cpp \
    battlecitycore.cpp \
    gameview.cpp \
    level.cpp \
    menutextitem.cpp

HEADERS += \
    BattleCityCore_global.h \
    GraphicsSceneObjects/GameObject.h \
    GraphicsSceneObjects/staticbody.h \
    GraphicsScenes/gamescene.h \
    GraphicsScenes/menuscene.h \
    battlecitycore.h \
    gameview.h \
    level.h \
    menutextitem.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
