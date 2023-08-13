cmake_minimum_required(VERSION 3.5)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(
    SOURCE_TARGET_NAME figures-target
)

add_library(
    ${SOURCE_TARGET_NAME} 
        STATIC
            figurebase.h
            figurebase.cpp
            square.h
            square.cpp
            rectangle.h
            rectangle.cpp
            circle.h
            circle.cpp
            triangle.h
            triangle.cpp
            figureaction.h
            figureaction.cpp
            startdrawing.h
            startdrawing.cpp
            continuedrawing.h
            continuedrawing.cpp
            completedrawing.h
            completedrawing.cpp
)

target_link_libraries(
    ${SOURCE_TARGET_NAME}
        PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets)

target_include_directories(
    ${SOURCE_TARGET_NAME} 
        PRIVATE
            ${CMAKE_BINARY_DIR})
