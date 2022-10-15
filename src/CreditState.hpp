#ifndef CREDITSTATE_HPP
#define CREDITSTATE_HPP

#include "Game.hpp"
#include "GameStates.hpp"

/*
  Music:  Flavio Concini, andrew-paglinawan
  Font:  AJ Paglia

  Inspired by Dodge, made by Eddy Rashed and Oskar Zanota
  https://www.lexaloffle.com/bbs/?pid=61949#p
*/

class CreditState : public GameState
{
    private:
      int centerOfscreen;

      SDL_Color color = {255, 255, 255 ,255};

      Sprite* TitleText = nullptr;
      Sprite* TextRad1 = nullptr;
      Sprite* TextRad2 = nullptr;
      Sprite* TextRad3 = nullptr;
      Sprite* TextRad4 = nullptr;

      Sprite* TextRad5 = nullptr;
      Sprite* TextRad6 = nullptr;
      Sprite* TextRad7 = nullptr;

      Sprite* TextRad8 = nullptr;

    public:
      CreditState();
      ~CreditState();

      void HandleEvents();
      void Update();
      void Render();

};

#endif
