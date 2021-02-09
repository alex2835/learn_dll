cmake_minimum_required(VERSION 3.12)
project(Main VERSION 1.0.0)

add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/dynalo)

add_subdirectory(window)
add_subdirectory(ui)