#include "player.h"

void Player::render(SDL_Renderer* renderer) {

    SDL_Rect playerRect;
    playerRect.x = position.x * size;
    playerRect.y = position.y * size;
    playerRect.h = size;
    playerRect.w = size;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &playerRect);
    SDL_RenderCopy(renderer, playerTex, NULL, &playerRect);
}

bool Player::isInside(int minX, int minY, int maxX, int maxY) {
    return (minX<=position.x && position.x+size<=maxX &&
            minY<=position.y && position.y+size<=maxY);
}
void Player::move(Direction direction) {
    Position newPosition = position.move(direction);
    position = newPosition;
    // game.playerMoveTo(newPosition);
}
