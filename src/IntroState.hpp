#ifndef INTROSTATE_HPP
#define INTROSTATE_HPP

#include "Game.hpp"
#include "GameStates.hpp"


class Sprite;
class Intro : public GameState
{
  private:
    Sprite* titleimage = nullptr;

    Sprite* playButtonSprite = nullptr;
    Sprite* creditButtonSprite = nullptr;
    Sprite* exitButtonSprite = nullptr;

    Sprite* SoundOnButtonSprite = nullptr;
    Sprite* SoundOffButtonSprite = nullptr;

    int CenterOfScreen = 0;
    float b1Size = 3.0f;
    float b2Size = 3.0f;
    float b3Size = 3.0f;

    // Test
    float alf = 0.0f;
    float duration = 500.0f;
    bool stopFade = false;
    Uint32 elapsedTime = 0;
    Uint32 startTime = 0;
    float titleImage_ypos = 0.0f;

  public:
    Intro();
    ~Intro();

    void HandleEvents();
    void Update();
    void Render();

};

#endif
