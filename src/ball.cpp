#include "ball.hpp"
#include "vector.hpp"
#include "assert.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "utils.hpp"
#include <random>
#include <numbers>
#include <vector>
#include <algorithm>

Ball::Ball(int x, int y, int radius) {
    assert(radius > 0);
    this->radius = radius;
    this->pos = Vector2<float>(x, y);
}

Ball::~Ball(void) {}

Ball::Ball(int radius, SDL_Rect box) {
    assert(radius > 0);
    this->radius = radius;

    static std::default_random_engine gen;
    std::uniform_int_distribution<int> x_axis(
        box.x + radius, box.x + box.w - radius
    );
    std::uniform_int_distribution<int> y_axis(
        box.y + radius, box.y + box.h - radius
    );

    this->pos = Vector2<float>(
        x_axis(gen), y_axis(gen)
    );
}

int Ball::getRadius(void) const {
    return this->radius;
}

void Ball::setRadius(int radius) {
    this->radius = radius;
}

int Ball::getDiameter(void) {
    return 2 * this->radius;
}

void Ball::setPos(int x, int y) {
    this->pos = Vector2<float>(x, y);
}

std::ostream& operator<<(std::ostream& os, const Ball& ball) {
    os << "Ball(" << "pos=" << ball.pos << ", " << "radius=" << ball.radius << ")";
    return os;
}

float Ball::distWith(Ball other) {
    return std::sqrt(
        std::pow(other.pos.getX() - this->pos.getX(), 2) + \
        std::pow(other.pos.getY() - this->pos.getY(), 2)
    );
}

void Ball::process(float delta) {

}

void Ball::render(SDL_Renderer* renderer) {
    filledCircleRGBA(
        renderer, this->pos.getX(), this->pos.getY(), this->radius,
        UNPACK_SDL_Color(this->color)
    );
}

bool Ball::collidingWith(const Ball& other) {
    return this->distWith(other) < this->getRadius() + other.getRadius();
}

Side Ball::collidingWith(const SDL_Rect& viewport) {
    
    if (this->pos.getX() - this->radius < viewport.x)
        return Side::LEFT;
    if (this->pos.getX() + this->radius > viewport.x + viewport.w)
        return Side::RIGHT;
    if (this->pos.getY() - this->radius < viewport.y)
        return Side::UP;
    if (this->pos.getY() + this->radius > viewport.y + viewport.h)
        return Side::DOWN;
    
    return Side::NONE;
}

// bool Ball::collidingWith(const std::vector<MovingBall> &balls) {
//     return (std::any_of(
//         balls.begin(), balls.end(), [&](Ball b2) {
//             return this->collidingWith(b2);
//         }
//     ));
// }


void MovingBall::initSpeed(int speed) {
    static std::default_random_engine gen;
    std::uniform_real_distribution<float> distribution(0, 2 * std::numbers::pi);

    this->speed = Vector2<float>(
        std::cos(distribution(gen)) * speed,
        std::sin(distribution(gen)) * speed
    );
}

MovingBall::MovingBall(int x, int y, int radius, int speed)
    : Ball(x, y, radius) {
    this->initSpeed(speed);
}

MovingBall::MovingBall(int radius, SDL_Rect box, int speed)
    : Ball(radius, box) {
    this->initSpeed(speed);
}

void MovingBall::process(float delta) {
    this->pos += this->speed * delta;
}

bool MovingBall::collidingWith(const std::vector<MovingBall> &balls) {
    return (std::any_of(
        balls.begin(), balls.end(), [&](Ball b2) {
            return this->collidingWith(b2);
        }
    ));
}

void MovingBall::resolveCollision(const SDL_Rect& viewport) {
    Side s = collidingWith(viewport);
    switch (s) {
    case Side::LEFT:
    case Side::RIGHT:
        this->speed.negX();
        break;
    case Side::UP:
    case Side::DOWN:
        this->speed.negY();
        break;
    default:
        break;
    }
}

void MovingBall::resolveCollision(MovingBall& other) {
    // Gérer les KOLLISIONS
    std::swap(this->speed, other.speed);
}
