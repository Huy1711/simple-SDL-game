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

    void move(Direction direction){
        switch(direction) {
            case UP:
                //if (y > 0 && !map1[y-1][x])
                    y -= 1;
                break;
            case DOWN:
                //if (y < 30-1 && !map1[y+1][x])
                    y += 1;
                break;
            case LEFT:
                //if (x > 0 && !map1[y][x-1])
                    x -= 1; break;
            case RIGHT:
                //if (x < 20-1 && !map1[y][x+1])
                x += 1; break;
        }
    }
};

#endif // POSITION_H
