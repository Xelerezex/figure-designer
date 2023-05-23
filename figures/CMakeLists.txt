cmake_minimum_required(VERSION 3.5)

set(
    SOURCE_TARGET_NAME figures-target
)

add_library(
    ${SOURCE_TARGET_NAME} 
        STATIC
        figures.h
        figures.cpp)

target_include_directories(
    ${SOURCE_TARGET_NAME} 
        PUBLIC
        ${CMAKE_BINARY_DIR})
