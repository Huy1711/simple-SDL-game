#ifndef Vector2D_h
#define Vector2D_h

struct Vector2D {
    float x;
    float y;

    Vector2D() {
        x = 0;
        y = 0;
    }

    Vector2D(float _x, float _y) {
        x = _x;
        y = _y;
    }

    Vector2D& operator*=(float n) {
        this->x *= n;
        this->y *= n;
        return *this;
    }

};

#endif // Vector2D_h
