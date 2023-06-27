#ifndef BALL_H
#define BALL_H

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include "vector.hpp"
#include "renderer.hpp"

enum class Side {
    NONE = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Ball {
    protected:
        int mRadius;
        Vector2<float> mPos = Vector2<float>(0, 0);
        SDL_Color mColor = {255, 0, 0, 255};
    public:
        Ball(float x, float y, int radius);
        Ball(int radius, SDL_Rect box);
        virtual ~Ball();
        int getRadius(void) const;
        void setRadius(int radius);
        int getDiameter(void);
        friend std::ostream& operator<<(std::ostream& os, const Ball& ball);
        void setPos(Vector2<float> pos);
        Vector2<float> getPos(void);
        virtual void process(float delta);
        virtual void render(Renderer& renderer);
        virtual bool collidingWith(const Ball& other);
        virtual Side collidingWith(const SDL_Rect& viewport);
        //virtual bool collidingWith(const std::vector<MovingBall> &balls); // A revoir
        float distWith(Ball other);
};

#endif
