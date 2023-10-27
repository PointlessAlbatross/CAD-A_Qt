cmake_minimum_required(VERSION 3.5)

project(CAD-A_Qt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Core Gui Charts DataVisualization)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core Gui Charts DataVisualization)

set(PROJECT_SOURCES
    src/antennaArrayParametersHex.cpp
    src/antennaArrayParametersRect.cpp
    src/arrangementOfElements.cpp
    src/cadAMath.cpp
    src/calcParam.cpp
    src/carrierParameters.cpp
    src/channelParameters.cpp
    src/chartsParameters.cpp
    src/echoSignal.cpp
    src/main.cpp
    src/mainwindow.cpp
    src/operatingSystemParameters.cpp
    src/patternCharts.cpp
    src/plot3d.cpp
    src/reverberationParameters.cpp
    src/selectWeight.cpp
    src/selectionOfCorrectiveElements.cpp
    src/workingEnvironmentSettings.cpp

    headers/antennaArrayParametersHex.h
    headers/antennaArrayParametersRect.h
    headers/arrangementOfElements.h
    headers/cadAMath.h
    headers/calcParam.h
    headers/carrierParameters.h
    headers/channelParameters.h
    headers/chartsParameters.h
    headers/echoSignal.h
    headers/mainwindow.h
    headers/operatingSystemParameters.h
    headers/patternCharts.h
    headers/plot3d.h
    headers/reverberationParameters.h
    headers/selectWeight.h
    headers/selectionOfCorrectiveElements.h
    headers/workingEnvironmentSettings.h


    mainwindow.ui
    arrangementOfElements.ui
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CAD-A_Qt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET CAD-A_Qt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(CAD-A_Qt SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CAD-A_Qt
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CAD-A_Qt PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Charts
    Qt${QT_VERSION_MAJOR}::DataVisualization)

set_target_properties(CAD-A_Qt PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS CAD-A_Qt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CAD-A_Qt)
endif()
