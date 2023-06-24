#ifndef PLAYER_H
#define PLAYER_H

#include "ball.hpp"

class Player {
    private:
        Ball ball;

    public:
        Player(int x, int y);
        virtual ~Player(void);
        void setPos(int x, int y);
        Ball getBall(void);
        void process(float delta);
        void render(SDL_Renderer* renderer);
};

#endif
