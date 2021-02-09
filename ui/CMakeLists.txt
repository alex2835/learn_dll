cmake_minimum_required(VERSION 3.18)
project(UI VERSION 1.0.0)


set(SOURCES
    src/ui.h
    src/ui.cpp
)

add_library(UI SHARED ${SOURCES})

target_link_libraries(UI imgui)

target_include_directories(
    UI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/dynalo/include
)