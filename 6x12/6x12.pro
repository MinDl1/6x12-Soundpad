QT += widgets
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 3): QT +=widgets

TARGET = 6x12
TEMPLATE = app

SOURCES += main.cpp \
        widget.cpp \

RESOURCES =6x12.qrc

HEADERS += widget.h

FORMS += widget.ui
