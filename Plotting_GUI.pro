QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    app/mainwindow \
    app/uart \
    libs/qcustomplot

# VPATH += \
#     app/mainwindow \
#     app/uart \
#     libs/qcustomplot

SOURCES += \
    app/mainwindow/mainwindow.cpp \
    app/mainwindow/mainwindow_data_scale.cpp \
    app/mainwindow/mainwindow_graph.cpp \
    app/mainwindow/mainwindow_horiztal_config.cpp \
    app/mainwindow/mainwindow_operation.cpp \
    app/mainwindow/mainwindow_vertical_config.cpp \
    app/uart/uart.cpp \
    libs/qcustomplot/qcustomplot.cpp \
    main.cpp \



HEADERS += \
    app/mainwindow/mainwindow.h \
    app/uart/uart.h \
    libs/qcustomplot/qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
