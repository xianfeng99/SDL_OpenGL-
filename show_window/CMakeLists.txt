cmake_minimum_required(VERSION 3.16)
project(show_window)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/Cellar/sdl2/2.0.14_1/include/)
link_directories(/usr/local/Cellar/sdl2/2.0.14_1/lib )

add_executable(show_window main.cpp)

target_link_libraries(
        show_window
        SDL2
        "-framework OpenGL"
)