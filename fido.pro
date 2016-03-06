!include("../Common/retroshare_plugin.pri"):error("Could not include file ../Common/retroshare_plugin.pri")

CONFIG += qt \
    uic \
    qrc \
    resources

greaterThan(QT_MAJOR_VERSION, 4) {
    #Qt 5
    QT += widgets
}

SOURCES = \
    p3Fido.cpp \
    FidoPlugin.cpp \
    helpers.cpp

HEADERS = \
    p3Fido.h \
    FidoPlugin.h \
    helpers.h

LIBS += -lmimetic

TARGET = Fido
