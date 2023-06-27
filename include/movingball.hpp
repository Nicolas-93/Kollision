#include "ball.hpp"
#include "vector.hpp"

class MovingBall: public Ball {
    private:
        Vector2<float> mSpeed = Vector2<float>(1, 1);
        void initSpeed(int speed);

    public:
        MovingBall(int x, int y, int radius, int speed);
        MovingBall(int radius, SDL_Rect box, int speed);
        void setSpeed(int speed);
        using Ball::collidingWith;
        bool collidingWith(const std::vector<MovingBall> &balls);
        void resolveCollision(MovingBall &other);
        void resolveCollision(const SDL_Rect &viewport);
        void process(float delta);
};
