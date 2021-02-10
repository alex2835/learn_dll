cmake_minimum_required(VERSION 3.18)
project(MainWindow VERSION 1.0.0)


set(SOURCES
    src/main.cpp
)

add_executable(MainWindow ${SOURCES})


set_target_properties(
    MainWindow PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(MainWindow imgui)
target_link_libraries(MainWindow UI)

target_include_directories(
    MainWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glfw/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/DHR

)

target_link_directories(
    MainWindow PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glfw/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glew/lib
)


if (APPLE)
    target_link_libraries(
        MainWindow
        libglfw3.a
        libGLEW.a
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework Carbon"
    )

elseif (WIN32)
    target_link_libraries(
        MainWindow
        glfw3.lib
        glew32s.lib
        opengl32.lib
    )
    ## Copy UI dll into executable dir
    #add_custom_command(
    #    TARGET MainWindow POST_BUILD
    #    COMMAND ${CMAKE_COMMAND} -E copy_directory
    #    $<TARGET_FILE_DIR:UI>
    #    $<TARGET_FILE_DIR:MainWindow>
    #)
endif()