cmake_minimum_required(VERSION 3.23)

project(MockArduinoCore LANGUAGES C CXX ASM)

add_library(arduino_MockCore
    ${CMAKE_CURRENT_LIST_DIR}/MockArduino.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Print.cpp
    ${CMAKE_CURRENT_LIST_DIR}/Stream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WString.cpp
    ${CMAKE_CURRENT_LIST_DIR}/itoa.c
)

target_include_directories(arduino_MockCore PUBLIC ${CMAKE_CURRENT_LIST_DIR})