QT += gui core widgets

TEMPLATE = lib
DEFINES += BATTLECITYCORE_LIBRARY

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GraphicsSceneObjects/GameObject.cpp \
    battlecitycore.cpp \
    level.cpp

HEADERS += \
    BattleCityCore_global.h \
    GraphicsSceneObjects/GameObject.h \
    battlecitycore.h \
    level.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
