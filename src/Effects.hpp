#ifndef EFFECTS_HPP
#define EFFECTS_HPP

#include <vector>
#include "Game.hpp"

/*
    Collection of effects
*/
class SimpleExplosion : public GameObject
 {
  public:
    SimpleExplosion(int x, int y);


    void HandleEvents();
    void Update();
    void Render();

  private:
    float speed;
    int debrieSize;
    int totalDebries;
    int lifetime;
    int life;

    std::vector<SDL_Rect> debrie;

    SDL_Color orgRenderColor;

 };


#endif
