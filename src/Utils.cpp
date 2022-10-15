#include "Utils.hpp"


bool checkCollision( SDL_Rect a, SDL_Rect b )
{
  //The sides of the rectangles
  int leftA, leftB;
  int rightA, rightB;
  int topA, topB;
  int bottomA, bottomB;

  //Calculate the sides of rect A
  leftA = a.x;
  rightA = a.x + a.w;
  topA = a.y;
  bottomA = a.y + a.h;

  //Calculate the sides of rect B
  leftB = b.x;
  rightB = b.x + b.w;
  topB = b.y;
  bottomB = b.y + b.h;

  //If any of the sides from A are outside of B
  if( bottomA <= topB )
      return false;

  if( topA >= bottomB )
      return false;

  if( rightA <= leftB )
      return false;

  if( leftA >= rightB )
      return false;

  //If none of the sides from A are outside B
  return true;
};

float Lerp(float start_value, float end_value, float pct)
{
    return (start_value + (end_value - start_value) * pct);
}

float EaseIn(float t)
{
    return t * t;
}

float Flip(float x)
{
    return 1 - x;
}

float Square(float t)
{
  return t*t;
}

float EaseOut(float t)
{
    return Flip(Square(Flip(t)));
}
