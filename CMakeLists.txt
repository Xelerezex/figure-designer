cmake_minimum_required(VERSION 3.5)

project(figure-designer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        centralwidget.h
        centralwidget.cpp
        figurescene.h
        figurescene.cpp
        figureview.h
        figureview.cpp
        sceneobject.h
        sceneobject.cpp
        squaresceneobject.h
        squaresceneobject.cpp
        rectanglesceneobject.h
        rectanglesceneobject.cpp
        trianglesceneobject.h
        trianglesceneobject.cpp
        circlesceneobject.h
        circlesceneobject.cpp
)

set(PROJECT_RESOURCES
        resources.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(figure-designer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET figure-designer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(figure-designer SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_RESOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(figure-designer
            ${PROJECT_SOURCES}
            ${PROJECT_RESOURCES}
        )
    endif()
endif()

include_directories(${PROJECT_SOURCE_DIR}/figures)
add_subdirectory(${PROJECT_SOURCE_DIR}/figures)

target_link_libraries(figure-designer
                      PRIVATE
                            Qt${QT_VERSION_MAJOR}::Widgets
                            figures-target)

set_target_properties(figure-designer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS figure-designer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(figure-designer)
endif()
