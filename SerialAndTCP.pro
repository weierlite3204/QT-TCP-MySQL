QT       += core gui sql charts network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    debugging.cpp \
    main.cpp \
    msgworker.cpp \
    mysql.cpp \
    mytcpserver.cpp \
    tcpdata.cpp \
    widget.cpp

HEADERS += \
    debugging.h \
    msgworker.h \
    mysql.h \
    mytcpserver.h \
    tcpdata.h \
    widget.h

FORMS += \
    debugging.ui \
    mysql.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
