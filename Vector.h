#ifndef Vector_h
#define Vector_h
#include <iostream>
#include <iomanip>
using namespace std;

struct Vector2D {
    float x;
    float y;

    Vector2D(float _x, float _y) {
    x = _x;
    y = _y;
    }

    Vector2D() {
        x=0;
        y=0;
    }

    Vector2D operator+(const Vector2D& v) const{
        Vector2D result;
        result.x = x+v.x;
        result.y = y+v.y;
        return result;
    }

    Vector2D operator-(const Vector2D& v) const{
        Vector2D result;
        result.x = x-v.x;
        result.y = y-v.y;
        return result;
    }

    Vector2D& operator+=(const Vector2D& v){
        this->x += v.x;
        this->y += v.y;
        return *this;
    }

    Vector2D& operator-=(const Vector2D& v){
        this->x -= v.x;
        this->y -= v.y;
        return *this;
    }

    Vector2D& operator*=(const float n) {
        this->x *= n;
        this->y *= n;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector2D& vect) {
        out << "(" << fixed << setprecision(2) <<
        vect.x << ", " << vect.y << ")" << endl;
        return out;
    }

};

#endif // Vector_h
