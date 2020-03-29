#include "painter.h"
#include <SDL.h>
#include <cstdlib>
#include <cmath>

Painter::Painter(SDL_Window* window, SDL_Renderer* renderer_)
    : renderer(renderer_)
{
	int width, height;
    SDL_RenderGetLogicalSize(renderer, &width, &height);
    if (width == 0 && height == 0)
        SDL_GetWindowSize(window, &width, &height);

    setPosition(width/2, height/2);
    setAngle(0);
    setColor(WHITE_COLOR);
    clearWithBgColor(BLUE_COLOR);
}

void Painter::setPosition(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Painter::setAngle(float angle)
{
    this->angle = angle
        - floor(angle/360)*360;
}

void Painter::setColor(SDL_Color color)
{
    this->color = color;
    SDL_SetRenderDrawColor(
        renderer, color.r, color.g, color.b, 0);
}

void Painter::clearWithBgColor(SDL_Color bgColor) const
{
  SDL_SetRenderDrawColor(
     renderer, bgColor.r, bgColor.g, bgColor.b, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(
     renderer, color.r, color.g, color.b, 0);
}

void Painter::moveForward(float length)
{
    float prevX = x, prevY = y;
    jumpForward(length);
    SDL_RenderDrawLine(renderer, (int)prevX, (int)prevY, (int)x, (int)y);
}

void Painter::jumpForward(float length)
{
    float rad = (angle / 180) * M_PI;
    x += cos(rad) * length;
    y -= sin(rad) * length;
}

void Painter::setRandomColor()
{
   Uint8 r = rand() % 256;
   Uint8 g = rand() % 256;
   Uint8 b = rand() % 256;
   SDL_Color color = { r, g, b };
   setColor(color);
}
