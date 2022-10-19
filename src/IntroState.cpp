#include "IntroState.hpp"

Intro::Intro() {

  CenterOfScreen = Game::GetWidth()/2;

  titleimage = new Sprite(Game::CreateTexture("title_size22_Dodgee.png"));
  titleimage->SetAlpha(0); // Start invisible

  playButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  playButtonSprite->SetClip({0,26,76,26});

  creditButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  creditButtonSprite->SetClip({0,0,93,26});

  exitButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  exitButtonSprite->SetClip({0,52,65,26});

  SoundOnButtonSprite = new Sprite(Game::CreateTexture("sound_on.png"));
  SoundOffButtonSprite = new Sprite(Game::CreateTexture("sound_off.png"));

  startTime = SDL_GetTicks();
  titleImage_ypos = -45;
}


Intro::~Intro()
{
  delete titleimage;
  delete playButtonSprite;
  delete creditButtonSprite;
  delete exitButtonSprite;
  delete SoundOnButtonSprite;
  delete SoundOffButtonSprite;
}

void Intro::Update() {

  // Fade in Title image
  if(!stopFade) {
    elapsedTime = SDL_GetTicks() - startTime;

    alf = Lerp(0.0f, 255.0f, EaseIn(elapsedTime / duration));
    titleImage_ypos = Lerp(-45.0f, 0.0f, EaseIn(elapsedTime / duration));

    if(alf >= 255) {
      stopFade = true;
      alf = 255;
      titleImage_ypos = 0;
    }

    titleimage->SetAlpha(alf);
  }
}

void Intro::HandleEvents()
{

  while( SDL_PollEvent( &event ) )
  {
    if( event.type == SDL_QUIT )
    {
        Game::SetNextState( STATE_EXIT );
    } else if( ( event.type == SDL_KEYDOWN )) {

      switch( event.key.keysym.sym )
      {
          case SDLK_ESCAPE:
          Game::SetNextState( STATE_EXIT );
          break;

          // ...
      }
    }
  }
}

void Intro::Render()
{

  // Note: Buttons are drawn from its center, not top-left corner
  Game::RenderTexture(titleimage->GetTexture(), CenterOfScreen - (titleimage->GetWidth()*4)/2, titleImage_ypos, 4.0f);

  // The buttons are handled almost exactly the same. Extract to a function!
  switch (GUI::Button(playButtonSprite->GetTexture(), playButtonSprite->GetClip(), CenterOfScreen, 400, b1Size)) {
    case BUTTON_IDLE: b1Size = 3.0f; break;
    case BUTTON_HOVER: b1Size = 3.5f; break;
    case BUTTON_PRESSED: b1Size = 3.5f; break;
    case BUTTON_RELEASED: b1Size = 3.5f; Game::SetNextState( STATE_INGAME ); break;
  }

  switch (GUI::Button(creditButtonSprite->GetTexture(), creditButtonSprite->GetClip(), CenterOfScreen, 500, b2Size)) {
    case BUTTON_IDLE: b2Size = 3.0f; break;
    case BUTTON_HOVER: b2Size = 3.5f; break;
    case BUTTON_PRESSED: b2Size = 3.5f; break;
    case BUTTON_RELEASED: b2Size = 3.5f; Game::SetNextState( STATE_CREDITS ); break;
  }

  switch (GUI::Button(exitButtonSprite->GetTexture(), exitButtonSprite->GetClip(), CenterOfScreen, 600, b3Size)) {
    case BUTTON_IDLE: b3Size = 3.0f; break;
    case BUTTON_HOVER: b3Size = 3.5f; break;
    case BUTTON_PRESSED: b3Size = 3.5f; break;
    case BUTTON_RELEASED: b3Size = 3.5f; Game::SetNextState( STATE_EXIT ); break;
  }

  // Zeroed out SDL_Rect {0,0,0,0} indecated the GUI to use single image and not the idle, hover, pressed states
  if(!Game::GetMuteState()) {
    if(GUI::Button(SoundOnButtonSprite->GetTexture(), {0,0,0,0}, Game::GetWidth() - SoundOnButtonSprite->GetWidth()-10, Game::GetHeight() - SoundOnButtonSprite->GetHeight()-5, 1) == BUTTON_RELEASED)
      Game::ToggleMute();
  } else {
    if(GUI::Button(SoundOffButtonSprite->GetTexture(), {0,0,0,0}, Game::GetWidth() - SoundOnButtonSprite->GetWidth()-10, Game::GetHeight() - SoundOnButtonSprite->GetHeight()-5, 1) == BUTTON_RELEASED)
      Game::ToggleMute();
  }

  Game::SetRenderColor({0, 0, 0, 255});
}
