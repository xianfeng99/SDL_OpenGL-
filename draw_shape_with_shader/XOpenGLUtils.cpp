//
// Created by 李显峰 on 2021/6/28.
//

#include <cstdio>
#include <cstring>
#include "XOpenGLUtils.h"


GLuint XOpenGLUtils::loadShader(GLenum type, const char * code, int32_t len)
{
    GLuint shader = glCreateShader(type);

    if(shader != 0)
    {
        glShaderSource(shader, 1, &code, &len);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        GLenum err = glGetError();
        if(compiled != 0)
        {
            return shader;
        } else {
            GLchar infoLog[512];
            glGetShaderInfoLog(shader, 512, &len, infoLog);
            printf("-----%s\n", infoLog);
            glDeleteShader(shader);
        }
    }

    return 0;
}

GLuint XOpenGLUtils::createProgram(const char * vertex_shader_code,
                                 const char * fragment_shader_code)
{
    size_t vertex_shader_len = strlen(vertex_shader_code);
    size_t fragment_shader_len = strlen(fragment_shader_code);
    GLuint vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_code, vertex_shader_len);
    if(!vertex_shader)
    {
        GLenum err = glGetError();
        return -1001;
    }

    GLuint fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_code, fragment_shader_len);
    if(!fragment_shader)
    {
        glDeleteShader(vertex_shader);
        GLenum err = glGetError();
        return -1002;
    }

    GLuint program = glCreateProgram();
    if(program)
    {
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        glLinkProgram(program);

        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if(linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            glDeleteProgram(program);
            program = 0;
        }
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}