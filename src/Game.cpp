#include "Game.hpp"

// Declear static members
SDL_Renderer* Game::SDLRenderer = nullptr;
SDL_Window* Game::SDLWindow = nullptr;
int Game::shakeX = 0;
int Game::shakeY = 0;
int Game::SCREEN_WIDTH  = 640;
int Game::SCREEN_HEIGHT = 720;
int Game::nextState = STATE_NULL;
unsigned Game::Highscore = 0;
unsigned Game::PreviousMouseState = 0;
unsigned Game::CurrentMouseState = 0;
int Game::MouseX = 0;
int Game::MouseY = 0;
Mix_Music* Game::Music = nullptr;
Mix_Chunk* Game::explotion = nullptr;
Mix_Chunk* Game::death = nullptr;
bool Game::Mute = false;


Game::~Game() {

  //Delete game state and free state resources
  delete currentState;

  // destroy renderer
  SDL_DestroyRenderer(SDLRenderer);

	// destroy window
	SDL_DestroyWindow(SDLWindow);

  //Free the music
	Mix_FreeMusic( Music );

  //Free the sound effects
  Mix_FreeChunk( explotion );
  Mix_FreeChunk( death );

  Mix_CloseAudio();

  // Clean up all initialized subsystems.
  TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Game::Initialize()
{
  //Start up SDL and make sure it went ok
	if (SDL_Init(SDL_INIT_VIDEO) != 0){
    debug(LOG_ERROR) << "SDL_Init: " << SDL_GetError() << std::endl;
		return 1;
	}
  SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY, 0); // Set to Nearest

  // Initilze TFF lib
  if (TTF_Init() != 0){
    debug(LOG_ERROR) << "TTF_Init: " << SDL_GetError() << std::endl;
  	SDL_Quit();
  	return 1;
  }

  //Initialize SDL_mixer
  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
  {
    debug(LOG_ERROR) << "MIXER_Init: " << SDL_GetError() << std::endl;
  	SDL_Quit();
  	return 1;
  }

  //Setup our window and renderer
	SDLWindow = SDL_CreateWindow("Dodgee!!", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, (SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI));
	if (SDLWindow == nullptr){
    debug(LOG_ERROR) << "CreateWindow: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}


	SDLRenderer = SDL_CreateRenderer(SDLWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (SDLRenderer == nullptr){
    debug(LOG_ERROR) << "CreateRenderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(SDLWindow);
		SDL_Quit();
		return 1;
	}

  // Enable alpha blending with RenderDraw functions
  SDL_SetRenderDrawBlendMode(SDLRenderer, SDL_BLENDMODE_BLEND);

  //Set the current state ID
  stateID = STATE_INTRO;

  //Set the current game state object
  currentState = new Intro();

  // Load Sound and Music assets
  explotion = Mix_LoadWAV( "assets/sfx/sfx_exp_various5.wav" );
  if(!explotion)
    debug(LOG_ERROR) << "Loading sounds: " << SDL_GetError() << std::endl;

  death = Mix_LoadWAV( "assets/sfx/what-are-you-doing.wav" );
  if(!death)
    debug(LOG_ERROR) << "Loading sounds: " << SDL_GetError() << std::endl;

  Music = Mix_LoadMUS( "assets/sfx/music_greek555.wav" );
  if(!Music)
    debug(LOG_ERROR) << "Loading music: " << SDL_GetError() << std::endl;


  return 0;
}

int Game::GetWidth() {
  return SCREEN_WIDTH;
}

int Game::GetHeight() {
  return SCREEN_HEIGHT;
}

unsigned Game::GetHighScore() {
  return Highscore;
}

void Game::SetHighScore(unsigned score) {
  Highscore = score;
}

void Game::AddToHighscore(unsigned value) {
  Highscore += value;
}

void Game::ClearScreen() {
  SDL_RenderClear(SDLRenderer);
}


void Game::ChangeState()
{
  //If the state needs to be changed
  if( nextState != STATE_NULL )
  {
      //Delete the current state
      if( nextState != STATE_EXIT )
      {
        delete currentState;
      }

      //Change the state
      switch( nextState )
      {
          case STATE_INTRO:
              currentState = new Intro();
              break;
          case STATE_CREDITS:
              currentState = new CreditState();
              break;
          case STATE_INGAME:
              currentState = new InGame();
              break;
      }

      //Change the current state ID
      stateID = nextState;

      //set STATE_NULL to next state ID, STATE_NULL means that we dont want to change state
      nextState = STATE_NULL;
  }

}


void Game::SetNextState( int state ) {
  if( nextState != STATE_EXIT )
      nextState = state;
}

void Game::PlaySound(SoundEffect sound) {

  if(Mute)
    return;

  // Error check? Mix_PlayChannel returns -1 on fail..
  switch (sound) {
    case EXPLOTION1: Mix_PlayChannel( -1, explotion, 0 ); break;
    case DEATH: Mix_PlayChannel( -1, death, 0 ); break;
  }
}

void Game::PlayMusic() {

  if(Mute)
    return;

	if(Mix_PlayingMusic() == 0) {
		Mix_PlayMusic( Music, -1 ); //Play the music
	} else {
    //If the music is paused
		if( Mix_PausedMusic() == 1 )
				Mix_ResumeMusic();  //Resume the music

  }
}

void Game::StopMusic() {
  Mix_HaltMusic();
}

void Game::PauseMusic() {
  Mix_PauseMusic();
}

void Game::ToggleMute() {
  Mute = Mute ? false : true;
}

bool Game::GetMuteState() {
  return Mute;
}

void Game::SetMouse(int x, int y) {
  SDL_WarpMouseInWindow(SDLWindow, x, y);
}


SDL_Texture* Game::CreateText(const std::string &text, const std::string &fontfile, SDL_Color color, int size, int style) {
  if(text.empty())
    return nullptr;

  std::string fontpath = "assets/fonts/" + fontfile;
  //Open the font
  TTF_Font* font = TTF_OpenFont(fontpath.c_str(), size);
  if (font == nullptr){
    debug(LOG_ERROR) << "TTF_OpenFont: " << SDL_GetError() << "assets/fonts/" << fontfile.c_str() << std::endl;
    return nullptr;
  }

  TTF_SetFontStyle(font, style);

  //We need to first render to a surface as that's what TTF_RenderText
  //returns, then load that surface into a texture

  SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), color);
  if (surf == nullptr){
    TTF_CloseFont(font);
    debug(LOG_ERROR) << "TTF_RenderText: " << SDL_GetError() << std::endl;
    return nullptr;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(SDLRenderer, surf);
  if (texture == nullptr){
    debug(LOG_ERROR) << "CreateTexture: " << SDL_GetError() << std::endl;
  }

  //Clean up the surface and font
  SDL_FreeSurface(surf);
  TTF_CloseFont(font);
  return texture;
}


SDL_Texture* Game::CreateTexture(const std::string &file) {
  std::string fontpath = "assets/bilder/" + file;

	SDL_Texture *texture = IMG_LoadTexture(SDLRenderer, fontpath.c_str());

	if (texture == nullptr){
    debug(LOG_ERROR) << "LoadTexture: " << SDL_GetError() << std::endl;
    return nullptr;
  }

	return texture;
}

void Game::RenderTexture(SDL_Texture *tex, SDL_Rect dst, SDL_Rect *clip) {
	SDL_RenderCopy(SDLRenderer, tex, clip, &dst);
}

void Game::RenderTexture(SDL_Texture *tex, int x, int y, SDL_Rect *clip) {
	SDL_Rect dst;
	dst.x = x + shakeX;
	dst.y = y + shakeY;
	if (clip != nullptr){
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else {
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}

	RenderTexture(tex, dst, clip);
}

void Game::RenderTexture(SDL_Texture *tex, int x, int y, float scale) {
	SDL_Rect dst;
  SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);

	dst.x = x;
	dst.y = y;
  dst.w *= scale;
  dst.h *= scale;

	RenderTexture(tex, dst, nullptr);
}

void Game::RenderLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(SDLRenderer, x1, y1, x2, y2);
}

void Game::RenderLine(int x1, int y1, int x2, int y2, SDL_Color color) {
  SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
  RenderLine(x1+shakeX, y1+shakeY, x2+shakeX, y2+shakeY);
}

void Game::RenderFilledRect(const SDL_Rect* rect) {
  SDL_RenderFillRect(SDLRenderer, rect);
}

void Game::RenderRect(const SDL_Rect* rect) {

  SDL_Color org = GetRenderColor();
  // Draw bounding box for debugging pruposes
  SetRenderColor({255, 255, 255, 255});
  SDL_RenderDrawRect(SDLRenderer, rect);
  SetRenderColor(org);
}

void Game::SetRenderColor(SDL_Color color) {
  SDL_SetRenderDrawColor(SDLRenderer, color.r, color.g, color.b, color.a);
}

SDL_Color Game::GetRenderColor() {
  SDL_Color tmp;
  SDL_GetRenderDrawColor(SDLRenderer,&tmp.r, &tmp.g, &tmp.b, &tmp.a);
  return tmp;
}

void Game::SetShake(int x, int y) {
  shakeX = x;
  shakeY = y;
}

void Game::Run()
{
  int loops;

  // Setup background that will be rendering for every state
  int scrollOffsetY = -720; // Screen height
  Sprite* backgroundImage = new Sprite(Game::CreateTexture("BG.png"));

  unsigned int next_game_tick = SDL_GetTicks();

  //Start counting frames per second
	int countedFrames = 0;

  //The frames per second timer
	Timer fpsTimer;
	fpsTimer.start();

  // Game Loop!
  while( stateID != STATE_EXIT )
  {
      loops = 0;

      //Calculate fps
		  float avgFPS = countedFrames / ( fpsTimer.getTicks() / 1000.f );
			if( avgFPS > 2000000 )
			{
				avgFPS = 0;
			}

      // Ensure 50 ticks per second
      while( SDL_GetTicks() > next_game_tick && loops < MAX_FRAMESKIP) {

        //Do state event handling
        currentState->HandleEvents();
        Game::CurrentMouseState = SDL_GetMouseState(&Game::MouseX, &Game::MouseY);

        //Do state logic
        currentState->Update();

        //Change state if needed
        ChangeState();

        //Do state rendering
        Game::ClearScreen();

        if(scrollOffsetY >= 0)
          scrollOffsetY = -720;

        scrollOffsetY += 2;

        // Render background images
        RenderTexture(backgroundImage->GetTexture(),-30,scrollOffsetY);
        RenderTexture(backgroundImage->GetTexture(),-30,scrollOffsetY+720);

        currentState->Render();

        next_game_tick += SKIP_TICKS;
        loops++;

      }

      Game::PreviousMouseState = SDL_GetMouseState(NULL, NULL);
      // std::cout << "Average Frames Per Second " << avgFPS << std::endl;

      //Update the screen
      SDL_RenderPresent(SDLRenderer);

      countedFrames++;

  }

  delete backgroundImage;

}
