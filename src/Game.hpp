#ifndef GAME_HPP
#define GAME_HPP

#include <iomanip>
#include <iostream>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "Timer.hpp"
#include "GameObject.hpp"
#include "Sprite.hpp"
#include "GUI/GUI.hpp"
#include "GameStates.hpp"
#include "IntroState.hpp"
#include "InGameState.hpp"
#include "CreditState.hpp"
#include "logger.hpp"

/*
  The game starts from this class, and built up by diffrent States.
  ie. IntroState, InGameState..
*/

class Game
{
public:

  enum SoundEffect {
    EXPLOTION1,
    DEATH
  };

  Game() {};
  ~Game();

  int Initialize();
  void Run();

  void ChangeState();
  static void SetNextState(int state);

  static void PlaySound(SoundEffect sound);
  static void StopMusic();
  static void PlayMusic();
  static void PauseMusic();

  static void ClearScreen();

  static SDL_Texture* CreateText(const std::string &text, const std::string &font, SDL_Color color, int size, int style=TTF_STYLE_NORMAL);

  static SDL_Texture* CreateTexture(const std::string &file);

  static void RenderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip = nullptr);
  static void RenderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip = nullptr);
  static void RenderTexture(SDL_Texture *tex, int x, int y, float scale);

  static void RenderLine(int x1, int y1, int x2, int y2);
  static void RenderLine(int x1, int y1, int x2, int y2, SDL_Color color);

  static void RenderFilledRect(const SDL_Rect* rect);
  static void RenderRect(const SDL_Rect* rect);

  static void SetRenderColor(SDL_Color color);
  static SDL_Color GetRenderColor();

  static int GetWidth();
  static int GetHeight();

  static unsigned GetHighScore();
  static void SetHighScore(unsigned score);
  static void AddToHighscore(unsigned value);

  static void SetShake(int x, int y);

  static void ToggleMute();
  static bool GetMuteState();

  static void SetMouse(int x, int y);

  static unsigned PreviousMouseState;
  static unsigned CurrentMouseState;
  static int MouseX;
  static int MouseY;

private:
  static SDL_Renderer* SDLRenderer;
  static SDL_Window* SDLWindow;

  static int SCREEN_WIDTH;
  static int SCREEN_HEIGHT;
  static int SCALE_FACTOR;

  static unsigned Highscore;

  // Contant Game Speed with Maximum FPS
  const int TICKS_PER_SECOND = 50;
  const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
  const int MAX_FRAMESKIP = 10;

  int stateID = 0;
  static int nextState;

  static Mix_Music* Music;
  static Mix_Chunk* explotion;
  static Mix_Chunk* death;

  // Kanske finns ett snyggare sätt att fixa en shake?
  static int shakeX;
  static int shakeY;

  static bool Mute;

  GameState* currentState = nullptr;

  void HandleEvents();
};

#endif
