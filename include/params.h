#ifndef PARAMS_INCLUDED
#define PARAMS_INCLUDED

#include <string>
#include <SDL2/SDL.h>

typedef struct {
    struct {
        int width;
        int height;
    } win;
    std::string title;

    int nb_balls;
    int new_balls_delay;
} Config;

#endif
