#include "player.hpp"

Player::Player(int x, int y) : ball(Ball(x, y, 10)) {}

Player::~Player(void) {}

void Player::setPos(int x, int y) {
    this->ball.setPos(x, y);
}

void Player::process(float delta) {

}

void Player::render(SDL_Renderer* renderer) {
    this->ball.render(renderer);
}

Ball Player::getBall(void) {
    return this->ball; 
}
