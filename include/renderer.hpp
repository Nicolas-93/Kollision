#ifndef RENDERER_H
#define RENDERER_H

#include "config.h"
#include <SDL2/SDL.h>
#include <string>

class Renderer {
    private:
        SDL_Window* mWin;
        SDL_Renderer* mRenderer;
    public:
        Renderer(Config& conf);
        ~Renderer();
        SDL_Renderer* getRenderer(void);
};

#endif
