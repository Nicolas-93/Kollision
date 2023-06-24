#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "params.h"
#include "ball.hpp"
#include "player.hpp"
#include <vector>
#include <random>

class Game {
    private:
        Config conf;
        SDL_Renderer* renderer;
        SDL_Rect viewport;

        bool running = true;
        std::vector<MovingBall> balls;
        Player p1;
        void initMatch(void);

    public:
        Game(Config conf, SDL_Renderer* renderer);
        ~Game();
        void handle_event(void);
        void process(float delta);
        void render(SDL_Renderer* renderer);
        void run(void);
};

#endif
