#include "renderer.hpp"
#include <stdexcept>

Renderer::Renderer(Config& conf) {
    SDL_Init(SDL_INIT_VIDEO);
    mWin = SDL_CreateWindow(
        conf.title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        conf.win.width, conf.win.height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    mRenderer = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!mWin || !mRenderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        throw std::runtime_error("[Error] Init failed");
    }

    SDL_SetWindowTitle(mWin, conf.title.c_str());
    //SDL_SetWindowGrab(mWin, SDL_TRUE);
    SDL_RenderSetViewport(mRenderer, NULL);
}

Renderer::~Renderer() {
    SDL_Quit();
    mWin = NULL;
    mRenderer = NULL;
}

SDL_Renderer* Renderer::getRenderer(void) {
    return mRenderer;
}
