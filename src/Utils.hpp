#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

bool checkCollision( SDL_Rect a, SDL_Rect b );

float Lerp(float start_value, float end_value, float pct);

float EaseIn(float t);

float Flip(float x);

float Square(float t);

float EaseOut(float t);

#endif
