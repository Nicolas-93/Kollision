#ifndef PLAYER_H
#define PLAYER_H

#include "ball.hpp"
#include "renderer.hpp"

class Player {
    private:
        Ball mBall;

    public:
        Player(int x, int y);
        virtual ~Player(void);
        Vector2<float> getPos(void);
        void setPos(Vector2<float> pos);
        Ball& getBall(void);
        void handleInput(void);
        void process(float delta);
        void render(Renderer& renderer);
    friend class Board;
};

#endif
