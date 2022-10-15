#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <ostream>
#include "Game.hpp"
#include "Utils.hpp"

class Player : public GameObject
{
  public:

    Player();
    ~Player();

    void HandleEvents();
    void Update();
    void Render();

  private:
    SDL_Texture* playerSprite = nullptr;
    SDL_Texture* trailTextures[4] = {nullptr, nullptr, nullptr, nullptr};

    // For adding trail to player
    ivec2 positionHistory[4] = {{0,0}, {0,0}, {0,0}, {0,0}};
    int historyIndex = 0;

};

#endif
