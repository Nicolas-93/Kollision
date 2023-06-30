#ifndef BOARD_INCLUDED
#define BOARD_INCLUDED

#include <vector>
#include <random>
#include <thread>
#include "renderer.hpp"
#include "player.hpp"
#include "movingball.hpp"

class Board {
    private:
        SDL_Rect mViewport;
        std::vector<MovingBall> mBalls;
        Player mP1;
        std::thread mBallFactory;
        bool mRunning;
        int mNewBallsDelay;
    
        void initMatch(int nbBalls);
        void initBallFactory(void);

    public:
        Board(SDL_Rect viewport, int nbBalls, int newBallsDelay);
        ~Board();
        void handleInput(void);
        void process(float delta);
        void render(Renderer& renderer);
        void addBall(void);
        
        bool isRunning(void);
        const SDL_Rect& getViewport(void);
};

#endif
