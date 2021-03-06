#-------------------------------------------------
#
# Project created by QtCreator 2017-10-07T09:28:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeQtAirplanes
TEMPLATE = app
CONFIG += c++1z

SOURCES += main.cpp \
    bullet.cpp \
    player.cpp \
    enemy.cpp \
    entity.cpp \
    game.cpp

HEADERS  += \
    bullet.hpp \
    player.hpp \
    entity.hpp \
    enemy.hpp \
    game.hpp \
    texItem.hpp

FORMS    +=

#QMAKE_CXXFLAGS += -std=gnu++14

RESOURCES += \
    resources.qrc
