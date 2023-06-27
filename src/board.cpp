#include "board.hpp"
#include "player.hpp"
#include "utils.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <SDL2/SDL2_gfxPrimitives.h>

Board::Board(SDL_Rect viewport, int nbBalls) :
    mViewport(viewport),
    mP1(Player(viewport.w / 2, viewport.h / 2)),
    mRunning(true)
{
    initMatch(nbBalls);
}

Board::~Board() {
    
}

void Board::initMatch(int nbBalls) {
    for (int i = 0; i < nbBalls; ) {
        MovingBall mb = MovingBall(10, mViewport, 20);
        if (!mb.collidingWith(mBalls)) {
            mBalls.push_back(mb);
            i++;
        }
    }
}

void Board::handleInput(void) {
    
    SDL_Event ev;
    while (SDL_PollEvent(&ev)) {
        switch (ev.type) {
        case SDL_QUIT:
            mRunning = false;
        }
    }

    mP1.handleInput();
    const SDL_Rect& viewport = getViewport();
    
    auto radius = mP1.mBall.getRadius();
    auto pos = mP1.getPos();
    pos.x = std::clamp((int) pos.x, viewport.x + radius, viewport.x + viewport.w - radius);
    pos.y = std::clamp((int) pos.y, viewport.y + radius, viewport.y + viewport.h - radius);
    mP1.mBall.setPos(pos);
}

bool Board::isRunning(void) {
    return mRunning;
}

const SDL_Rect& Board::getViewport(void) {
    return mViewport;
}

void Board::process(float delta) {

    for (MovingBall& b: mBalls)
        b.process(delta);

    combinations(mBalls, 2, [&](auto &comb) {
        MovingBall &b1 = comb[0].get(), &b2 = comb[1].get();
        if (b1.collidingWith(b2)) {
            b1.resolveCollision(b2);
            std::cout << "Collided" << std::endl;
        }
    });

    for (MovingBall& b1 : mBalls) {
        b1.resolveCollision(mViewport);
        if (mP1.getBall().collidingWith(b1)) {
            // mrunning = false;
        }
    }
}

void Board::render(Renderer& renderer) {

    SDL_SetRenderDrawColor(
        renderer.getRenderer(),
        255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(
        renderer.getRenderer(),
        &mViewport);

    for (MovingBall& b: mBalls)
        b.render(renderer);
    mP1.render(renderer);
}

