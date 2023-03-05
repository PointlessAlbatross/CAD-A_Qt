QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    antenna_array_parameters_hex.cpp \
    antenna_array_parameters_rect.cpp \
    arrangementOfElements.cpp \
    main.cpp \
    mainwindow.cpp \
    operating_system_parameters.cpp \
    pattern_charts.cpp \
    select_weight.cpp
HEADERS += \
    antenna_array_parameters_hex.h \
    antenna_array_parameters_rect.h \
    arrangementOfElements.h \
    mainwindow.h \
    operating_system_parameters.h \
    pattern_charts.h \
    select_weight.h

FORMS += \
    antenna_array_parameters_hex.ui \
    antenna_array_parameters_rect.ui \
    arrangementOfElements.ui \
    mainwindow.ui \
    operating_system_parameters.ui \
    pattern_charts.ui \
    select_weight.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
