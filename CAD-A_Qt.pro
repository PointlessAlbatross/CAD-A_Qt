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
    cadAMath.cpp \
    carrierParameters.cpp \
    main.cpp \
    mainwindow.cpp \
    operatingSystemParameters.cpp \
    patternCharts.cpp \
    selectWeight.cpp \
    selectionOfCorrectiveElements.cpp \
    workingEnvironmentSettings.cpp
HEADERS += \
    antennaArrayParametersHex.h \
    antennaArrayParametersRect.h \
    arrangementOfElements.h \
    cadAMath.h \
    carrierParameters.h \
    mainwindow.h \
    operatingSystemParameters.h \
    patternCharts.h \
    selectWeight.h \
    selectionOfCorrectiveElements.h \
    workingEnvironmentSettings.h

FORMS += \
    antennaArrayParametersHex.ui \
    antennaArrayParametersRect.ui \
    arrangementOfElements.ui \
    carrierParameters.ui \
    mainwindow.ui \
    operatingSystemParameters.ui \
    patternCharts.ui \
    selectWeight.ui \
    selectionOfCorrectiveElements.ui \
    workingEnvironmentSettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
