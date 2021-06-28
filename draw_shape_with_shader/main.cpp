#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"
#include "SDL2/SDL_opengl.h"
#include "XOpenGLUtils.h"

/**
 * 部分代码借鉴网址：
 *  https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/04%20Hello%20Triangle/
 */

const char * vertex_shader = "attribute vec2 a_position;"
                             "void main() {"
                             "  gl_Position = vec4(a_position, 0.0, 1.0);"
                             "}";
const char * frag_shader = "void main() {"
                           " gl_FragColor = vec4(1.0, 0.0, 1.0, 1.0);"
                           "}";

GLuint m_program;
GLuint loc_vertex_attr;
GLfloat vertex_arr[16] = {
        -0.5f, -0.5f,
        0.0f, -0.5f,
        0.5f, -0.5f,
        0.5f, 0.f,
        0.5f, 0.5f,
        0.0f, 0.5f,
        -0.5f, 0.5f,
        -0.5f, 0.f
};

void drawOpenGLBorder();
void initProgram();
void draw_point();
void draw_line();
void draw_triangle();

GLuint VBO;
GLuint VAO;
void initProgram2();
void draw_point2();
void draw_line2();
void draw_triangle2();

GLuint indices[4] = {
    0, 2, 4, 6
};
GLuint EBO;
void initProgram3();
void draw_point3();
void draw_line3();
void draw_triangle3();

int main() {

    SDL_Window *window = SDL_CreateWindow("hello OpenGL", 0, 0, 300, 300, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

//    initProgram();
//    initProgram2();
    initProgram3();

    SDL_Event event;
    while (true) {
        //检查事件
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
        //位于window的位置
        glViewport(100, 100, 100, 100);
        //显示紫色
        glClearColor(1.f, 1.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        drawOpenGLBorder();

        //第一种方式绘制，需要调用initProgram()
//        draw_point();
//        draw_line();
//        draw_triangle();
        //使用VBO和VAO方式绘制，需要调用initProgram2()
//        draw_point2();
//        draw_line2();
//        draw_triangle2();
        //使用EBO方式, 需要调用initProgram3()
//        draw_point3();
//        draw_line3();
        draw_triangle3();
        //更新窗口
        SDL_GL_SwapWindow(window);
    }

    //销毁OpenGL Context
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void initProgram() {
    m_program = XOpenGLUtils::createProgram(vertex_shader, frag_shader);
    printf("-----m_program: %d\n", m_program);
    loc_vertex_attr = glGetAttribLocation(m_program, "a_position");
    printf("-----loc_vertex_attr: %d\n", loc_vertex_attr);
}

/**
 * 这个函数在此次渲染中，只是将窗口轮廓绘制出来
 */
void drawOpenGLBorder() {
    //将OpenGL渲染的窗口轮廓绘制出来
    glLineWidth(1);
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(0,0xAAAA);
    glColor3f(0.f, 0.f, 0.f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-1.f, -1.f);
    glVertex2f(1.f, -1.f);
    glVertex2f(1.f, 1.f);
    glVertex2f(-1.f, 1.f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);

    glBegin(GL_LINES);
    glVertex2f(-1.f, 0.f);
    glVertex2f(1.f, 0.f);
    glVertex2f(0.f, 1.f);
    glVertex2f(0.f, -1.f);
    glEnd();
}

void draw_point() {
    glUseProgram(m_program);
    glPointSize(10);
    glEnableVertexAttribArray(loc_vertex_attr);
    /**
     * 参数
     * GLuint index: 指向shader中的属性所对应的值，通过glGetAttribLocation(GLuint program, const GLchar *name)获取
     * GLint size: 坐标的size，如vec2，则为2
     * GLenum type: 坐标中数值类型，如vec2(1.0, 0.5),则类型为GL_FLOAT
     * GLboolean normalized：归一化，所有值被映射到0（有符号为-1）到1之间
     * GLsizei stride: 步长
     * const GLvoid *pointer：坐标数组
     */
    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_TRUE, 0, vertex_arr);
    /**
     * GLenum mode：渲染模式，包含GL_POINTS， GL_LINES, GL_LINE_LOOP, GL_LINE_STRIP, GL_TRIANGLES, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN
     * GLint first: 第几个顶点开始,网站（https://learnopengl-cn.readthedocs.io/zh/latest/01%20Getting%20started/04%20Hello%20Triangle/）说是数组的索引，我测试情况为第几个顶点，如有错误，欢迎指出，我会及时更正）
     * GLsizei count: 需要绘制的顶点数
     */
    glDrawArrays(GL_POINTS, 3, 3);
    glDisableVertexAttribArray(loc_vertex_attr);
    glUseProgram(0);
}

void draw_line() {
    glUseProgram(m_program);

    glEnableVertexAttribArray(loc_vertex_attr);
    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_TRUE, 0, vertex_arr);
    glDrawArrays(GL_LINES, 0, 2);

    glDrawArrays(GL_LINE_STRIP, 3, 3);
    glDisableVertexAttribArray(loc_vertex_attr);

    glUseProgram(0);
}

void draw_triangle() {
    //三个点组成一个三角形
    glUseProgram(m_program);
    glEnableVertexAttribArray(loc_vertex_attr);
//    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GL_FLOAT), vertex_arr);
    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_FALSE, 0, vertex_arr);
    glDrawArrays(GL_TRIANGLES, 1, 3);
    glDisableVertexAttribArray(loc_vertex_attr);
    glUseProgram(0);
}

void initProgram2() {
    m_program = XOpenGLUtils::createProgram(vertex_shader, frag_shader);
    printf("-----m_program: %d\n", m_program);
    loc_vertex_attr = glGetAttribLocation(m_program, "a_position");
    printf("-----loc_vertex_attr: %d\n", loc_vertex_attr);
    //生成VBO, VAO
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //绑定Buffer
    /**
     * GLenum target: buffer data 类型
     * GLsizeiptr size: buffer data 数据大小，字节为单位
     * const GLvoid *data: 实际数据指针(我在mac上实际测试结果是：glBufferData中的data可以为0，但glVertexAttribPointer最后一个参数必须为顶点数据数据)
     * GLenum usage：渲染方式
     */
    glBufferData(GL_VERTEX_ARRAY, sizeof(vertex_arr), vertex_arr, GL_STATIC_DRAW);
    /**
     * glVertexAttribPointer最后一个参数如果不是数据，会退出程序
     */
    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_FALSE, 0, vertex_arr);
    glEnableVertexAttribArray(loc_vertex_attr);
    //解绑VAO
    glBindVertexArray(0);

}

void draw_point2() {
    glPointSize(5);
    glUseProgram(m_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_POINTS, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}

void draw_line2() {
    glUseProgram(m_program);
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 1, 4);
    glDrawArrays(GL_LINE_LOOP, 4, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

void draw_triangle2() {
    glUseProgram(m_program);
    glBindVertexArray(VAO);
//    glDrawArrays(GL_TRIANGLES, 2, 6);
//    glDrawArrays(GL_TRIANGLE_STRIP, 1, 7);
    glDrawArrays(GL_TRIANGLE_FAN, 1, 4);
    glBindVertexArray(0);
    glUseProgram(0);
}

void initProgram3() {
    m_program = XOpenGLUtils::createProgram(vertex_shader, frag_shader);
    printf("-----m_program: %d\n", m_program);
    loc_vertex_attr = glGetAttribLocation(m_program, "a_position");
    printf("-----loc_vertex_attr: %d\n", loc_vertex_attr);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_arr), vertex_arr, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    /**
      * glVertexAttribPointer最后一个参数如果是数据，渲染会混乱（原因未知）
      */
    glVertexAttribPointer(loc_vertex_attr, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(loc_vertex_attr);

    glBindVertexArray(0);

}

void draw_point3() {
    glPointSize(5);
    glUseProgram(m_program);
    glBindVertexArray(VAO);
    glDrawElements(GL_POINTS, 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void draw_line3() {
    glUseProgram(m_program);
    glBindVertexArray(VAO);
    glDrawElements(GL_LINES, 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void draw_triangle3() {

    glUseProgram(m_program);
    glBindVertexArray(VAO);
//    glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
//    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 0);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, 0);
    glBindVertexArray(VAO);
    glUseProgram(0);


}