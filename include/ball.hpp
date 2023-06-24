#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "vector.hpp"

enum class Side {
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Ball {
    protected:
        int radius;
        Vector2<float> pos = Vector2<float>(0, 0);
        SDL_Color color = {255, 0, 0, 255};
    public:
        Ball(int x, int y, int radius);
        Ball(int radius, SDL_Rect box);
        virtual ~Ball();
        int getRadius(void) const;
        void setRadius(int radius);
        int getDiameter(void);
        friend std::ostream& operator<<(std::ostream& os, const Ball& ball);
        void setPos(int x, int y);
        virtual void process(float delta);
        virtual void render(SDL_Renderer* renderer);
        virtual bool collidingWith(const Ball& other);
        virtual Side collidingWith(const SDL_Rect& viewport);
        //virtual bool collidingWith(const std::vector<MovingBall> &balls); // A revoir
        float distWith(Ball other);
};

class MovingBall: public Ball {
    private:
        Vector2<float> speed = Vector2<float>(1, 1);
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

#endif
