#ifndef POSITION_H
#define POSITION_H
enum Direction {
    UP = 0, DOWN, LEFT, RIGHT
};

struct Position
{
    int x;
    int y;

    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_) {}

    bool operator==(Position p) const {
        return x == p.x && y == p.y;
    }

};

#endif // POSITION_H
