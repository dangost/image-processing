QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    histogramwindow.cpp \
    imgprocessing.cpp \
    lab01matrix.cpp \
    lab02core.cpp \
    main.cpp \
    mainwindow.cpp \
    secondwindow.cpp

HEADERS += \
    histogramwindow.h \
    imgprocessing.h \
    lab01matrix.h \
    lab02core.h \
    mainwindow.h \
    secondwindow.h

FORMS += \
    histogramwindow.ui \
    historam.ui \
    mainwindow.ui \
    secondwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    1.jpeg \
    3.jpg \
    4.jpg \
    icon.icns

ICON += icon.icns
QT_QPA_PLATFORM=wayland
