#include <chrono>
#include <thread>
#include "game.hpp"

using namespace std;

Game::Game(Config conf, Renderer& renderer) :
    mBoard(
        (SDL_Rect) {0, 0, conf.win.width, conf.win.height},
        conf.nb_balls, conf.new_balls_delay
    ),
    mRenderer(renderer)
{
    
}

Game::~Game() {
    
}


void Game::run(void) {

    const float FPS = 60.0f;
    const chrono::duration<float, chrono::milliseconds::period> frameDelay(100.0f / FPS);

    chrono::high_resolution_clock::time_point frameStart, frameEnd;
    chrono::duration<float, chrono::milliseconds::period> frameTime;
    float deltaTime = 0.0f;


    while (mBoard.isRunning()) {
        frameStart = chrono::high_resolution_clock::now();

        mBoard.handleInput();
        mBoard.process(deltaTime);
        mBoard.render(mRenderer);
        SDL_RenderPresent(mRenderer.getRenderer());

        frameEnd = chrono::high_resolution_clock::now();
        frameTime = frameEnd - frameStart;

        if (frameTime < frameDelay) {
            // Attendre le temps restant pour atteindre le frameDelay
            this_thread::sleep_for(frameDelay - frameTime);
        }

        deltaTime = clamp(frameTime.count() / 100.0f, 0.0f, 0.1f);
        // cout << deltaTime << endl;
    }
}

// void Board::run(void) {
//     constexpr float FPS = 60.0f;
//     constexpr float FRAMEDELAY = 1000.0f / FPS;

//     Uint32 frameStart, frameTime;
//     float deltaTime = 0.0f;

//     while (running) {
//         frameStart = SDL_GetTicks();

//         this->handle_event();
//         this->process(deltaTime);
//         this->render(this->renderer);
//         SDL_RenderPresent(this->renderer);

//         frameTime = SDL_GetTicks() - frameStart;
//         cout << deltaTime << endl;

//         if (frameTime < FRAMEDELAY) {
//             SDL_Delay((Uint32)(FRAMEDELAY - frameTime));
//         }

//         deltaTime = (float)frameTime / 1000.0f;
//     }
// }
