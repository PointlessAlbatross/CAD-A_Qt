QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    antennaArrayParametersHex.cpp \
    antennaArrayParametersRect.cpp \
    arrangementOfElements.cpp \
    main.cpp \
    mainwindow.cpp \
    operatingSystemParameters.cpp \
    patternCharts.cpp \
    selectWeight.cpp \
    selectionOfCorrectiveElements.cpp
HEADERS += \
    antennaArrayParametersHex.h \
    antennaArrayParametersRect.h \
    arrangementOfElements.h \
    mainwindow.h \
    operatingSystemParameters.h \
    patternCharts.h \
    selectWeight.h \
    selectionOfCorrectiveElements.h

FORMS += \
    antennaArrayParametersHex.ui \
    antennaArrayParametersRect.ui \
    arrangementOfElements.ui \
    mainwindow.ui \
    operatingSystemParameters.ui \
    patternCharts.ui \
    selectWeight.ui \
    selectionOfCorrectiveElements.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
