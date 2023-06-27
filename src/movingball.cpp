#include "movingball.hpp"
#include <numbers>
#include <random>

void MovingBall::initSpeed(int speed) {
    static std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution(0, 2 * std::numbers::pi);

    mSpeed = Vector2<float>(
        std::cos(distribution(gen)) * speed,
        std::sin(distribution(gen)) * speed
    );
}

MovingBall::MovingBall(int x, int y, int radius, int speed)
    : Ball(x, y, radius) {
    initSpeed(speed);
}

MovingBall::MovingBall(int radius, SDL_Rect box, int speed)
    : Ball(radius, box) {
    initSpeed(speed);
}

void MovingBall::process(float delta) {
    mPos += mSpeed * delta;
}

bool MovingBall::collidingWith(const std::vector<MovingBall> &balls) {
    return (std::any_of(
        balls.begin(), balls.end(), [&](Ball b2) {
            return collidingWith(b2);
        }
    ));
}

void MovingBall::resolveCollision(const SDL_Rect& viewport) {
    Side s = collidingWith(viewport);
    switch (s) {
    case Side::LEFT:
    case Side::RIGHT:
        mSpeed.negX();
        break;
    case Side::UP:
    case Side::DOWN:
        mSpeed.negY();
        break;
    default:
        break;
    }
}

void MovingBall::resolveCollision(MovingBall& other) {
    // KOLLISION !
    // std::swap(mSpeed, other.mSpeed);

    Vector2<float> v1 = mSpeed - \
        (mPos - other.mPos) * \
        ((2 * other.mRadius) / (mRadius + other.mRadius)) * \
        (((mSpeed - other.mSpeed) * (mPos - other.mPos)) / \
        (mPos - other.mPos).normSq());

    Vector2<float> v2 = other.mSpeed - \
        (other.mPos - mPos) * \
        ((2 * mRadius) / (mRadius + other.mRadius)) * \
        (((other.mSpeed - mSpeed) * (other.mPos - mPos)) / \
        (other.mPos - mPos).normSq());

    mSpeed = v1;
    other.mSpeed = v2;
}
