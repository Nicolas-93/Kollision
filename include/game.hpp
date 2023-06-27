#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "board.hpp"
#include "renderer.hpp"

class Game {
    private:
        Board mBoard;
        Renderer& mRenderer;

    public:
        Game(Config conf, Renderer& renderer);
        ~Game();

        void run(void);
};

#endif
