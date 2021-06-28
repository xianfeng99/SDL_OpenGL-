#include "SDL2/SDL.h"
#include "OpenGL/OpenGL.h"
#include "OpenGL/gl3.h"
#include "SDL2/SDL_opengl.h"

void drawOpenGLBorder();

void draw_point();
void draw_line();
void draw_triangle();
void draw_polygon();

int main() {

    SDL_Window *window = SDL_CreateWindow("hello OpenGL", 0, 0, 300, 300, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(window);

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
//        draw_point();
//        draw_line();
//        draw_triangle();
        draw_polygon();

        //更新窗口
        SDL_GL_SwapWindow(window);
    }

    //销毁OpenGL Context
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

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
    glPointSize(5);
    //使用BeginMode中的模式, 不能使用 GL_POINT, GL_LINE, GL_FILL,这些多边形模式（虚线，描边，填充）
    glBegin(GL_POINTS);
    //设置颜色，设置点的颜色为绿色
    glColor3f(0.f, 1.f, 0.f);
    //设置绘制位置，范围(-1.f, -1.f) - (1.f, 1.f)
    glVertex2d(1, 0);
    glVertex2f(0, 0.5);
    glVertex2f(0.5f, 0.5f);
    glEnd();
}

void draw_line() {

    //设置line宽度需要在glBegin前，否则不生效
    glLineWidth(2);
    glColor3f(0.f, 0.f, 1.f);
    //GL_LINES模式下，坐标一定要成对，两点为一线，出现奇数，则不进行这个点的绘制
    glBegin(GL_LINES);
    glVertex2f(-0.75f, 0.75f);
    glVertex2f(-0.25f, 0.75f);
    glVertex2f(-0.9f, 1.f);
    glVertex2f(-0.9f, -0.);
    glEnd();

    //设置line宽度需要在glBegin前，否则不生效
    glLineWidth(5);
    //GL_LINE_LOOP模式下，每一个点和下一个点进行相连，然后最后一个点和起点相连形成一个循环
    glBegin(GL_LINE_LOOP);
    glColor3f(1.f, 0.f, 0.f);
    glVertex2f(-0.9f, -0.1f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-0.1f, -0.1f);
    glVertex2f(-0.5f, -1.f);
    glEnd();

    //下一个点和上一个点相连
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glColor3f(1.f, 1.f, 0.f);
    glVertex2f(0.5f, 0.f);
    glVertex2f(0.5f, 1.f);
    glVertex2f(1.f, 1.f);
    glVertex2f(1.f, 0.f);
    glEnd();

}

void draw_triangle() {
    //三个点组成一个三角形
    glBegin(GL_TRIANGLES);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-1.f, 1.f);
    glVertex2f(0.f, 1.f);
    glEnd();
    //最后一个点和前两个点组成一个三角形，多个点依次进行组合
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(0.5f, 0.5f);
    glVertex2f(0.f, 1.f);
    glVertex2f(1.f, 1.f);
    glVertex2f(1.f, 0.f);
    glEnd();
    //起点和当前最后两个点组成，多个点依次进行组合
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.f, 0.f, 1.f);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(-1.f, -1.f);
    glVertex2f(-0.5f, -1.f);
    glVertex2f(0.f, -0.5f);
    glEnd();

//    glBegin(GL_TRIANGLE_FAN);
//    glVertex2f(0.f, -0.5f);
//    for (int i = 0; i <= 8; i ++) {
//        glColor3f(i * 0.125 * 1.f, 0.f, 1.f);
//        glVertex2f(cos(i * 3.14 / 4) / 2 + 0.5f, sin(i * 3.14 / 4) / 2 - 0.5f);
//    }
//    glEnd();
}

void draw_polygon() {
    glBegin(GL_POLYGON);
    glColor3f(1.f, 0.f, 1.f);
    glVertex2f(-0.5f, 0.5f);
    glVertex2f(-1.f, 1.f);
    glVertex2f(0.f, 1.f);
    glVertex2f(0.f, 0.5f);
    glEnd();
}