#include <SDL2/SDL.h>
#include <stdexcept>
#include "params.h"
#include "game.hpp"

static Config conf {
    .win = {
        .width = 600,
        .height = 480,
    },
    .title = "Kollision",
    .nb_balls = 10,
    .new_balls_delay = 10 /*s*/,
};

int main(void) {
    SDL_Window* win;
    SDL_Renderer* renderer;

    
    SDL_Init(SDL_INIT_VIDEO);
    win = SDL_CreateWindow(
        conf.title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        conf.win.width, conf.win.height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);

    if (!win || !renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
        throw std::runtime_error("[Error] Init failed");
    }

    SDL_SetWindowTitle(win, conf.title.c_str());
    SDL_SetWindowGrab(win, SDL_TRUE);
    SDL_RenderSetViewport(renderer, NULL);

    Game g = Game(conf, renderer);
    g.run();

    SDL_Quit();
}
