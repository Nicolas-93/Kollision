#include "player.hpp"

Player::Player(int x, int y) : mBall(x, y, 10) {}

Player::~Player(void) {}

void Player::setPos(Vector2<float> pos) {
    mBall.setPos(pos);
}

Vector2<float> Player::getPos(void) {
    return mBall.getPos();
}

void Player::handleInput(void) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    setPos(Vector2<float>(x, y));
}

void Player::process(float delta) {

}

void Player::render(Renderer& renderer) {
    mBall.render(renderer);
}

Ball& Player::getBall(void) {
    return mBall; 
}
