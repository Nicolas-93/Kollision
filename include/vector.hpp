#ifndef VECTOR_H
#define VECTOR_H
#include <iostream>

template <class T>
class Vector2 {
    private:
        T x = 0;
        T y = 0;
    public:
        Vector2(T x, T y) : x(x), y(y) {

        }
        Vector2(void) : x(0), y(0) {

        }
        ~Vector2() {
            
        }
        T getX(void) const {
            return x;
        }
        T getY(void) const {
            return y;
        }

        template<class U>
        friend std::ostream& operator<<(std::ostream& os, const Vector2<U> &vec);

        void negX(void) {
            this->x *= -1;
        }
        void negY(void) {
            this->y *= -1;
        }
        void operator+=(Vector2<T> const &other) {
            this->x += other.x;
            this->y += other.y;
        }
        void operator-=(Vector2<T> const &other) {
            this->x -= other.x;
            this->y -= other.y;
        }
        void operator*=(T n) {
            this->x *= n;
            this->y *= n;
        }

        Vector2<T> operator+(Vector2<T> b) {
            return Vector2<T>(x + b.getX(), y + b.getY());
        };
        Vector2<T> operator-(Vector2<T> b) {
            return Vector2<T>(x - b.getX(), y - b.getY());
        }
        T operator*(Vector2<T> b) {
            return (
                x * b.getX() +
                y * b.getY()
            );
        }
        Vector2<T> operator*(T n) {
            return Vector2<T>(x * n, y * n);
        }
};

template <class U>
std::ostream& operator<<(std::ostream& os, const Vector2<U> &vec) {
    os << "Vector(" << vec.getX() << ", " << vec.getY() << ")";
    return os;
}

#endif