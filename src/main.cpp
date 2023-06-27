#include "config.h"
#include "game.hpp"

Config conf = {
    .win = {
        .width = 600,
        .height = 480,
    },
    .title = "Kollision",
    .nb_balls = 10,
    .new_balls_delay = 10 /*s*/,
};

int main(void) {
    Renderer renderer(conf);

    Game g = Game(conf, renderer);
    g.run();

    return EXIT_SUCCESS;
}
