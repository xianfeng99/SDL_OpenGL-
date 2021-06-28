cmake_minimum_required(VERSION 3.16)
project(draw_shape_with_shader)

set(CMAKE_CXX_STANDARD 11)

include_directories(/usr/local/Cellar/sdl2/2.0.14_1/include/)
link_directories(/usr/local/Cellar/sdl2/2.0.14_1/lib )

add_executable(draw_shape_with_shader main.cpp XOpenGLUtils.cpp XOpenGLUtils.h)

target_link_libraries(
        draw_shape_with_shader
        SDL2
        "-framework OpenGL"
)