APP_NAME = phoneAbuser

CONFIG += qt warn_on cascades10

include(config.pri)

LIBS += -lbb -lbbsystem -lbbdata
QT += network

TRANSLATIONS = \
    $${TARGET}_fr.ts \
    $${TARGET}.ts