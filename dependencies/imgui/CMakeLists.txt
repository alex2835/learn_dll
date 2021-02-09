cmake_minimum_required(VERSION 3.12)
project(imgui VERSION 1.0.0)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_library(imgui STATIC ${SRCS} ${HDRS})

target_include_directories(
    imgui
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
)

add_definitions(-D"GLEW_STATIC")

target_include_directories(
    imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgui
)

target_link_directories(
    imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../glfw/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../glew/lib
)

if (APPLE)
    target_link_libraries(
        imgui
        libglfw3.a
        libGLEW.a
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework Carbon"
    )
endif()

if (WIN32)
    target_link_libraries(
        imgui
        glfw3.lib
        glew32s.lib
        opengl32.lib
)
endif()