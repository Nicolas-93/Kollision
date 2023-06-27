#include <assert.h>
#include <random>
#include <numbers>
#include <vector>
#include <algorithm>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "ball.hpp"
#include "vector.hpp"
#include "utils.hpp"

Ball::Ball(float x, float y, int radius) {
    setRadius(radius);
    mPos = Vector2<float>(x, y);
}

Ball::~Ball(void) {}

Ball::Ball(int radius, SDL_Rect box) {
    setRadius(radius);

    static std::default_random_engine gen;
    std::uniform_int_distribution<int> x_axis(
        box.x + mRadius, box.x + box.w - mRadius
    );
    std::uniform_int_distribution<int> y_axis(
        box.y + mRadius, box.y + box.h - mRadius
    );

    mPos = Vector2<float>(
        x_axis(gen), y_axis(gen)
    );
}

int Ball::getRadius(void) const {
    return mRadius;
}

void Ball::setRadius(int radius) {
    assert(radius > 0);
    mRadius = radius;
}

int Ball::getDiameter(void) {
    return 2 * mRadius;
}

void Ball::setPos(Vector2<float> pos) {
    mPos = pos;
}

Vector2<float> Ball::getPos() {
    return mPos;
}

std::ostream& operator<<(std::ostream& os, const Ball& ball) {
    os << "Ball(" << "mPos=" << ball.mPos << ", " << "radius=" << ball.mRadius << ")";
    return os;
}

float Ball::distWith(Ball other) {
    return std::sqrt(
        std::pow(other.mPos.getX() - mPos.getX(), 2) + \
        std::pow(other.mPos.getY() - mPos.getY(), 2)
    );
}

void Ball::process(float delta) {

}

void Ball::render(Renderer& renderer) {
    filledCircleRGBA(
        renderer.getRenderer(),
        mPos.getX(), mPos.getY(), mRadius,
        UNPACK_SDL_Color(mColor)
    );
}

bool Ball::collidingWith(const Ball& other) {
    return distWith(other) < getRadius() + other.getRadius();
}

Side Ball::collidingWith(const SDL_Rect& viewport) {
    
    if (mPos.getX() - mRadius < viewport.x)
        return Side::LEFT;
    if (mPos.getX() + mRadius > viewport.x + viewport.w)
        return Side::RIGHT;
    if (mPos.getY() - mRadius < viewport.y)
        return Side::UP;
    if (mPos.getY() + mRadius > viewport.y + viewport.h)
        return Side::DOWN;
    
    return Side::NONE;
}

// bool Ball::collidingWith(const std::vector<MovingBall> &balls) {
//     return (std::any_of(
//         balls.begin(), balls.end(), [&](Ball b2) {
//             return collidingWith(b2);
//         }
//     ));
// }

