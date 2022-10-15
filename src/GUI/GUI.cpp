#include "GUI.hpp"

namespace GUI
{

  // Note: singleImage is for buttons that only have one appearance
  // Note: from size and position of source, we calculate hover and pressed sprite
  ButtonState Button(SDL_Texture* spritesheet, SDL_Rect source, int x, int y, float scale)
  {
    bool singleImage = false;
    ButtonState returnValue = BUTTON_IDLE;

    // Size of 0,0,0,0 indicates a singleImage
    if(source.x == 0 && source.y == 0 && source.w == 0 && source.h == 0) {
      SDL_QueryTexture(spritesheet, NULL, NULL, &source.w, &source.h);
      singleImage = true;
    }

    SDL_Rect destination = {x,y, source.w*scale, source.h*scale};
    destination.x -= destination.w/2;
    destination.y -= destination.h/2;

    // Check if mouser is over me!
    if(Game::MouseX > destination.x && Game::MouseX < destination.x+destination.w) {
      if(Game::MouseY > destination.y && Game::MouseY < destination.y+destination.h) {

        returnValue = BUTTON_HOVER;

        if(!singleImage)
          source.x = source.x+source.w;  // Jump to hovering image

      if ((Game::CurrentMouseState & SDL_BUTTON_LMASK) != 0) {

        returnValue = BUTTON_PRESSED;


        if(!singleImage)
          source.x = source.x+source.w; // Jump to pressed image

      } else {

        if((Game::PreviousMouseState & SDL_BUTTON_LMASK) != 0)
          returnValue = BUTTON_RELEASED;

      }
     }
    }

    Game::RenderTexture(spritesheet, destination, &source);

    return returnValue;
  }

}
