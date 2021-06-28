#include "SDL2/SDL.h"
#include "OpenGL/gl3.h"

int main() {

    //创建OpenGL窗口
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
        glViewport(0, 100, 100, 100);
        //显示紫色
        glClearColor(1.f, 0.f, 1.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        //更新窗口
        SDL_GL_SwapWindow(window);
    }

    //销毁OpenGL Context
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
