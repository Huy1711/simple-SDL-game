#ifndef position_h
#define position_h

enum Direction {
    UP, DOWN, LEFT, RIGHT
};

struct Position {
    int x;
    int y;

    Position(int _x = 0, int _y = 0) : x(_x), y(_y) {}


    Position move(Direction direction) const {
        switch(direction) {
            case UP: return Position(x, y-1);
            case DOWN: return Position(x, y + 1);
    		case LEFT: return Position(x - 1, y);
    		case RIGHT: return Position(x + 1, y);
        }
    }

    bool isInsideBox(int left, int top, int width, int height) const {
        return x >= left && x < left+width && y >= top && y < top+height;
    }

    bool operator==(Position p) const {
        return x == p.x && y == p.y;
    }
};
#endif // position_h
