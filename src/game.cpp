#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <thread>
#include <iostream>
#include "game.hpp"
#include "player.hpp"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "utils.hpp"

Game::Game(Config conf, SDL_Renderer* renderer) :
    renderer(renderer), p1(Player(conf.win.width / 2, conf.win.height / 2))
{
    this->conf = conf;
    SDL_RenderGetViewport(renderer, &this->viewport);
    this->viewport = (SDL_Rect) {
        0, 0,
        this->conf.win.width, this->conf.win.height
    };
    this->initMatch();
    this->p1.setPos(this->viewport.w / 2, this->viewport.h / 2);
    //SDL_CaptureMouse(SDL_TRUE);
}

Game::~Game() {
}

void Game::initMatch(void) {
    for (int i = 0; i < this->conf.nb_balls; ) {
        MovingBall mb = MovingBall(10, this->viewport, 20);
        if (!mb.collidingWith(this->balls)) {
            this->balls.push_back(mb);
            i++;
        }
    }
}

void Game::handle_event(void) {
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
        case SDL_QUIT:
            this->running = false;
            break;
        }
    }
    int x, y;
    auto radius = p1.getBall().getRadius();
    SDL_GetMouseState(&x, &y);

    x = std::clamp(x, viewport.x + radius, viewport.x + viewport.w - radius);
    y = std::clamp(y, viewport.y + radius, viewport.y + viewport.h - radius);
    this->p1.setPos(x, y);
    std::cout << p1.getBall() << std::endl;
}

void Game::process(float delta) {

    for (MovingBall& b: this->balls)
        b.process(delta);

    combinations(balls, 2, [&](auto &comb) {
        MovingBall &b1 = comb[0].get(), &b2 = comb[1].get();
        if (b1.collidingWith(b2)) {
            b1.resolveCollision(b2);
        }
    });

    for (MovingBall& b1 : this->balls) {
        b1.resolveCollision(this->viewport);
        if (p1.getBall().collidingWith(b1)) {
            std::cout << "Collided" << std::endl;
            // this->running = false;
        }
    }
}

void Game::render(SDL_Renderer* renderer) {

    SDL_SetRenderDrawColor(this->renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(this->renderer, &this->viewport);

    for (MovingBall& b: this->balls)
        b.render(renderer);
    this->p1.render(renderer);
}

void Game::run(void) {
    const float FPS = 60.0f;
    const std::chrono::duration<float, std::chrono::milliseconds::period> frameDelay(100.0f / FPS);

    std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
    std::chrono::duration<float, std::chrono::milliseconds::period> frameTime;
    float deltaTime = 0.0f;

    while (running) {
        frameStart = std::chrono::high_resolution_clock::now();

        this->handle_event();
        this->process(deltaTime);
        this->render(this->renderer);
        SDL_RenderPresent(this->renderer);

        frameEnd = std::chrono::high_resolution_clock::now();
        frameTime = frameEnd - frameStart;

        if (frameTime < frameDelay) {
            // Attendre le temps restant pour atteindre le frameDelay
            std::this_thread::sleep_for(frameDelay - frameTime);
        }

        deltaTime = std::clamp(frameTime.count() / 100.0f, 0.0f, 0.1f);
        std::cout << deltaTime << std::endl;
    }
}

// void Game::run(void) {
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
//         std::cout << deltaTime << std::endl;

//         if (frameTime < FRAMEDELAY) {
//             SDL_Delay((Uint32)(FRAMEDELAY - frameTime));
//         }

//         deltaTime = (float)frameTime / 1000.0f;
//     }
// }
