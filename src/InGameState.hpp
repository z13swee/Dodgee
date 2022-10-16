#ifndef INGAMESTATE_HPP
#define INGAMESTATE_HPP

#include <vector>
#include <sstream>

#include "Game.hpp"
#include "GameStates.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Effects.hpp"

class Enemy;
class Player;
class InGame : public GameState
{
  public:

    InGame();
    ~InGame();

    void HandleEvents();
    void Update();
    void Render();

  private:

    enum InGameState { // Nice!
      COUNTDOWN,
      GAMEPLAY,
      GAMEOVER,
      MENU
    };

    void GameplayUpdate();
    void ResetGame();

    // Start in countdown state
    InGameState CurrentState = COUNTDOWN;

    SDL_Color color = { 255, 255, 255, 255 };

    bool countingDown = true;
    bool startShake = false;
    bool inGameMenu = false;



    /*
      Resources for ingame
    */
    Player* player = nullptr;

    Sprite* one = nullptr;
    Sprite* two = nullptr;
    Sprite* three = nullptr;
    Sprite* go = nullptr;

    Sprite* inGameHighScore = nullptr;
    Sprite* inGameTimer = nullptr;

    std::stringstream TimerStringStream;

    Uint32 Milliseconds,Seconds,Minutes = 0;
    Uint32 elapsedTime = 0;
    Uint32 gameStartTime = 0;
    Uint32 introStartTime = 0;

    bool startIntroTimer = false;
    bool startGameTimer = false;

    Uint8 introNumberIndex = 0;
    Uint8 spawnEnemyTimer = 0;
    Uint8 shakeTimer = 0;

    std::vector<GameObject*> gameObjects;

    /*
      Resources for ingame menu
    */

    Sprite* titleimage = nullptr;

    Sprite* continueButtonSprite = nullptr;
    Sprite* creditButtonSprite = nullptr;
    Sprite* exitButtonSprite = nullptr;

    int CenterOfScreen = 0;
    float b1Size = 3.0;
    float b2Size = 3.0;
    float b3Size = 3.0;
    int mx = 0;
    int my = 0;


    /*
      Resources for Game Over screen
    */

    Sprite* titleText = nullptr;
    Sprite* totalScoreText = nullptr;
    Sprite* infoText = nullptr;

};

#endif
