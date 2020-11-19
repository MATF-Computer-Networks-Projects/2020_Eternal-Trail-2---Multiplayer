cmake_minimum_required(VERSION 3.17)
project(2020_Eternal_Trail_2___Multiplayer)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
add_subdirectory(glad/)
add_subdirectory(glm/)

add_executable(ET2M main.cpp Shader.cpp Shader.hpp)

target_link_libraries(ET2M glm glad glfw OpenGL::GL
                      pthread X11 Xrandr Xi dl Xxf86vm Xinerama Xcursor glm)

