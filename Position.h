#ifndef position_h
#define position_h
#include "Vector.h"

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Position {
    Vector2D position;
    Vector2D velocity;
    int speed = 10;

    Position();
    Position(float _x, float _y);

    void init() {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() {
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};
#endif // position_h
