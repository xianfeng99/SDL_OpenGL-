cmake_minimum_required(VERSION 3.16)
project(draw_shape)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/Cellar/sdl2/2.0.14_1/include/)
link_directories(/usr/local/Cellar/sdl2/2.0.14_1/lib )

add_executable(draw_shape main.cpp )

target_link_libraries(
        draw_shape
        SDL2
        "-framework OpenGL"
)