TEMPLATE = app

QT += qml quick multimedia widgets

SOURCES += main.cpp \
    VideoProducer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    VideoProducer.h
