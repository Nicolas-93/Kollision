#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <random>
#include "renderer.hpp"
#include "player.hpp"
#include "movingball.hpp"

class Board {
    private:
        SDL_Rect mViewport;
        std::vector<MovingBall> mBalls;
        Player mP1;
        bool mRunning;
    
        void initMatch(int nbBalls);

    public:
        Board(SDL_Rect viewport, int nbBalls);
        ~Board();
        void handleInput(void);
        void process(float delta);
        void render(Renderer& renderer);
        
        bool isRunning(void);
        const SDL_Rect& getViewport(void);
};

#endif
