QT       += core gui charts datavisualization

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    antennaArrayParametersHex.cpp \
    antennaArrayParametersRect.cpp \
    arrangementOfElements.cpp \
    cadAMath.cpp \
    calcParam.cpp \
    carrierParameters.cpp \
    channelParameters.cpp \
    chartsParameters.cpp \
    echoSignal.cpp \
    main.cpp \
    mainwindow.cpp \
    operatingSystemParameters.cpp \
    patternCharts.cpp \
    plot3d.cpp \
    reverberationParameters.cpp \
    selectWeight.cpp \
    selectionOfCorrectiveElements.cpp \
    workingEnvironmentSettings.cpp
HEADERS += \
    antennaArrayParametersHex.h \
    antennaArrayParametersRect.h \
    arrangementOfElements.h \
    cadAMath.h \
    calcParam.h \
    carrierParameters.h \
    channelParameters.h \
    chartsParameters.h \
    echoSignal.h \
    mainwindow.h \
    operatingSystemParameters.h \
    patternCharts.h \
    plot3d.h \
    reverberationParameters.h \
    selectWeight.h \
    selectionOfCorrectiveElements.h \
    workingEnvironmentSettings.h

FORMS += \
    antennaArrayParametersHex.ui \
    antennaArrayParametersRect.ui \
    arrangementOfElements.ui \
    calcParam.ui \
    carrierParameters.ui \
    channelParameters.ui \
    chartsParameters.ui \
    echoSignal.ui \
    mainwindow.ui \
    operatingSystemParameters.ui \
    patternCharts.ui \
    reverberationParameters.ui \
    selectWeight.ui \
    selectionOfCorrectiveElements.ui \
    workingEnvironmentSettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
