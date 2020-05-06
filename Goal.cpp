#include "Goal.h"

Goal::Goal(SDL_Renderer *ren, int x, int y) {
    renderer = ren;
    goalTex = Gallery::loadTexture("warp.jpg", renderer);
    position.x = x;
    position.y = y;
}

void Goal::update(){
    goalRect.x = position.x;
    goalRect.y = position.y;
    goalRect.w = 3*30;
    goalRect.h = 5*30;
}

void Goal::setPosition(int x, int y) {
    position.x = x;
    position.y = y;
    update();
}

void Goal::render(SDL_Renderer* renderer) {
    update();
    SDL_RenderCopy(renderer, goalTex, NULL, &goalRect);
}

void Goal::move(Direction direction) {
    switch(direction) {
        case UP: position.y -= 1*speed; break;
        case DOWN: position.y += 1*speed; break;
        case LEFT: position.x -= 1*speed; break;
        case RIGHT: position.x += 1*speed; break;
    }
}

bool Goal::canMove(Direction direction, int map[20][30]){
    switch(direction) {
        case LEFT: return (position.x > 0 && map[position.y/30][(position.x)/30]==0);
        case RIGHT: return (position.x < 900-30*3 && map[position.y/30][(position.x)/30+3]==0);
        case UP: return (position.y > 0 && map[position.y/30][position.x/30]==0);
        case DOWN: return  (position.y < 600-30*5 && map[(position.y)/30+5][position.x/30]==0);
    }
}

void Goal::movingGoal(const Player &player, int map[20][30]) {
    int distanceX = abs(player.position.x - position.x);
    int distanceY = abs(player.position.y - position.y);
    if (position.x < player.position.x && position.y >= player.position.y) {
        if(distanceX<=distanceY && canMove(DOWN, map))
            move(DOWN);
        else if (distanceX>distanceY && canMove(LEFT, map))
            move(LEFT);
    } else if(position.x >= player.position.x && position.y > player.position.y) {
        if(distanceX<=distanceY && canMove(DOWN, map))
            move(DOWN);
        else if (distanceX>distanceY && canMove(RIGHT, map))
            move(RIGHT);
    } else if (position.x > player.position.x && position.y <= player.position.y) {
        if(distanceX<=distanceY && canMove(UP, map))
            move(UP);
        else if (distanceX>distanceY && canMove(RIGHT, map))
            move(RIGHT);
    } else if (position.x <= player.position.x && position.y < player.position.y) {
        if(distanceX<=distanceY && canMove(UP, map))
            move(UP);
        else if (distanceX>distanceY && canMove(LEFT, map))
            move(LEFT);
    }
}
