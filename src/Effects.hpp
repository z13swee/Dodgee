#ifndef EFFECTS_HPP
#define EFFECTS_HPP
/*
    Collection of effects
*/
#include <vector>
#include "Game.hpp"

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
