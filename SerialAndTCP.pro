QT       += core gui sql network serialport printsupport

# 添加QCustomPlot支持
INCLUDEPATH += $$PWD
HEADERS += $$PWD/qcustomplot.h
SOURCES += $$PWD/qcustomplot.cpp

# 添加Qxlsx支持
include($$PWD/QXlsx/QXlsx.pri)
INCLUDEPATH += $$PWD/QXlsx

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debugging.cpp \
    databaseworker.cpp \
    main.cpp \
    msgworker.cpp \
    mysql.cpp \
    mytcpserver.cpp \
    widget.cpp

HEADERS += \
    databaseworker.h \
    debugging.h \
    msgworker.h \
    mysql.h \
    mytcpserver.h \
    sensordata.h \
    widget.h

FORMS += \
    debugging.ui \
    mysql.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
