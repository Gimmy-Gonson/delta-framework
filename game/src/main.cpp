#include <SDL3/SDL.h>
#include <delta/delta.hpp>

const uint32_t WIDTH = 1280;
const uint32_t HEIGHT = 960;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("CoolGame", WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        return -1;
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    Delta::init();

    Delta::Renderer renderer = {WIDTH, HEIGHT};

    Delta::Rect rect = {{1.0f, 2.0f}, 100, 100};

    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                running = false;
            }
        }

        renderer.clear(1.0f, 1.0f, 1.0f, 1.0f);
        renderer.drawRect(rect);

        SDL_GL_SwapWindow(window);
    }

    SDL_Quit();
    return 0;
}
