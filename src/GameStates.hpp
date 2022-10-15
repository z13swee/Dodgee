#ifndef GAMESTATES_HPP
#define GAMESTATES_HPP

/*
  Base class for game states
*/
enum GameStates
{
  STATE_NULL,
  STATE_INTRO,
  STATE_INGAME,
  STATE_CREDITS,
  STATE_EXIT,
};

class GameState
{
  public:
    SDL_Event event;

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual ~GameState() {};

  private:

};

#endif
