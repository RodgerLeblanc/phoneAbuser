APP_NAME = phoneAbuserService

CONFIG += qt warn_on

include(config.pri)

LIBS += -lbb -lbbsystem -lbbplatform -lbbdevice -lbbdata
QT += network