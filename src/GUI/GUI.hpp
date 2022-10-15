#ifndef GUI_HPP
#define GUI_HPP

#include "../Game.hpp"

/*
  This implementation is tailord to projects needs, like
  the use of design rules like buttons expects spritesheet with
  button order: idle, hover, pressed

*/


enum ButtonState {
  BUTTON_IDLE,
  BUTTON_HOVER,
  BUTTON_PRESSED,
  BUTTON_RELEASED
  };

namespace GUI
{
  // Note: from size and position of idleSprite, we calculate hover and pressed sprite
  ButtonState Button(SDL_Texture* spritesheet, SDL_Rect idleSprite, int x, int y, float scale = 1.0f);
};

#endif
