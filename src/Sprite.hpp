#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Game.hpp"

class Sprite
{
public:

  Sprite();
  Sprite(SDL_Texture* texture);
  Sprite(const std::string path);
  ~Sprite();

  void SetClip(SDL_Rect clip);
  void SetColor(int r, int g, int b);
  void SetAlpha(int alpha);

  SDL_Rect GetClip();
  SDL_Texture* GetTexture();
  int GetWidth();
  int GetHeight();
  int GetMidPointX();
  int GetMidPointY();

private:
  SDL_Texture* SourceTexture = nullptr;
  SDL_Rect Clip = {0,0,0,0};
  int Width = 0;
  int Height = 0;
  int midPointX = 0;
  int midPointY = 0;
};

#endif
