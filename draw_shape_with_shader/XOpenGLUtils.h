//
// Created by 李显峰 on 2021/6/28.
//

#ifndef DRAW_SHAPE_BIND_COORDINATES_XOPENGLUTILS_H
#define DRAW_SHAPE_BIND_COORDINATES_XOPENGLUTILS_H

#include "OpenGL/gl3.h"

class XOpenGLUtils {
public:
    static GLuint loadShader(GLenum type, const char * code, int32_t len);
    static GLuint createProgram(const char * vertex_shader_code, const char * fragment_shader_code);
};


#endif //DRAW_SHAPE_BIND_COORDINATES_XOPENGLUTILS_H
