#include <SDL2/SDL.h>
#include "InGameState.hpp"

InGame::InGame() {

  // Hide cursor
  SDL_ShowCursor(SDL_DISABLE);

  CenterOfScreen = Game::GetWidth()/2;

  // Set background color
  Game::SetRenderColor({0, 0, 0, 255});

  /*
    Resources for Countdown
  */
  // These assets don't require folder? For example assets/fonts/...ttf
  one = new Sprite(Game::CreateText("1", "AldotheApache.ttf", color, 182));
  two = new Sprite(Game::CreateText("2", "AldotheApache.ttf", color, 182));
  three = new Sprite(Game::CreateText("3", "AldotheApache.ttf", color, 182));
  go = new Sprite(Game::CreateText("GO!!", "AldotheApache.ttf", color, 182, TTF_STYLE_ITALIC));

  inGameTimer = new Sprite(Game::CreateText("01:54:00", "AldotheApache.ttf", color, 28, TTF_STYLE_ITALIC));

  // Create player
  player = new Player();
  gameObjects.push_back(player);

  /*
    Resources for ingame menu
  */
  titleimage = new Sprite(Game::CreateTexture("title_size22_Dodgee.png"));

  continueButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  continueButtonSprite->SetClip({0,78,125,26});

  creditButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  creditButtonSprite->SetClip({0,0,93,26});

  exitButtonSprite = new Sprite(Game::CreateTexture("title_buttons_spritesheet.png"));
  exitButtonSprite->SetClip({0,52,65,26});



  /*
    Resources for Game Over screen
  */
  std::string highscorestring = "With a highscore of: " + std::to_string(Game::GetHighScore());

  titleText = new Sprite(Game::CreateText("YOU DIED!", "AldotheApache.ttf", color, 56));
  totalScoreText = new Sprite(Game::CreateText(highscorestring, "AldotheApache.ttf", color, 22));
  infoText = new Sprite(Game::CreateText("ESC to exit, or any other key to play again!", "AldotheApache.ttf", color, 16));



}

InGame::~InGame() {

  for(unsigned i = 0; i < gameObjects.size(); i++)
    delete gameObjects[i];

  delete one;
  delete two;
  delete three;
  delete go;

  delete inGameHighScore;
  delete inGameTimer;

  delete titleimage;

  delete continueButtonSprite;
  delete creditButtonSprite;
  delete exitButtonSprite;

  delete titleText;
  delete totalScoreText;
  delete infoText;
}

void InGame::HandleEvents()
{
  while( SDL_PollEvent( &event ) )
  {
    //If the user has Xed out the window
    if( event.type == SDL_QUIT )
    {
        Game::SetNextState( STATE_EXIT );
    }

    else if( ( event.type == SDL_KEYDOWN ))
    {
      switch (event.key.keysym.sym){
        case SDLK_ESCAPE:
          switch (CurrentState) {
            case GAMEPLAY: {
              CurrentState = MENU;
              SDL_GetMouseState(&mx, &my);
              SDL_ShowCursor(SDL_ENABLE);
              break;
            }
            case GAMEOVER: {
              Game::SetNextState( STATE_EXIT );
              break;
            }
            case MENU: {
              Game::SetNextState( STATE_EXIT );
              break;
            }
            case COUNTDOWN: { break; }
          }

          break;

        default:
          if(CurrentState == GAMEOVER)
            ResetGame();
          break;
      }
    }
  }
}

void InGame::ResetGame() {
  SDL_ShowCursor(SDL_DISABLE);

  Game::SetHighScore(0);
  CurrentState = COUNTDOWN;

  startGameTimer = false;

  // Clear enemies
  for(unsigned i = 0; i < gameObjects.size(); i++)
    if(gameObjects[i] != player)
      delete gameObjects[i];

  gameObjects.clear();

  // Revive player
  player->isValid = true;
  gameObjects.push_back(player);

}

void InGame::Update() {

  switch (CurrentState) {
    case COUNTDOWN: return; break;
    case GAMEPLAY: GameplayUpdate(); break;
    case GAMEOVER: return; break;
    case MENU: break;
  }
}

void InGame::GameplayUpdate() {

  // Start ingame timer
  if(!startGameTimer) {
    gameStartTime = SDL_GetTicks();
    startGameTimer = true;
  }

  // Check for collision
  for(unsigned i=0; i < gameObjects.size(); ++i) {
    if(!gameObjects[i]->isCollidable)
     continue;

    for(unsigned k=0; k < gameObjects.size(); ++k) {
      if(!gameObjects[k]->isCollidable)
       continue;

      // Dont check same object against itself
      if(i != k) {

        // Prevent checking same collision twice
        if(gameObjects[i]->isValid && gameObjects[k]->isValid ) {
          if(checkCollision( gameObjects[i]->collisionBox, gameObjects[k]->collisionBox)) {

            gameObjects[i]->isValid = false;
            gameObjects[k]->isValid = false;

            // Check if it was the player who died
            if(!player->isValid) {

              Game::PlaySound(Game::DEATH);

              // Add elapsed time bonus (1point per second)
              Game::AddToHighscore(elapsedTime/1000);

              startGameTimer = false;
              elapsedTime = 0;
              CurrentState = GAMEOVER;
              continue;

              // For debbuging ;)
              // player->isValid = true;

            } else {
              // ..else add to Highscore
              Game::PlaySound(Game::EXPLOTION1);

              Game::AddToHighscore(1);
              startShake = true;
              shakeTimer = 0;  // Reset timer for each explosion
              gameObjects.push_back(new SimpleExplosion(gameObjects[i]->position.x, gameObjects[i]->position.y));

            }
          }

        }

      }
    }
  }

  // Shake
  if(startShake) {
    Game::SetShake(rand() % 18 +1, rand() % 18 +1);
    shakeTimer += 1;

    if(shakeTimer > 15) {
      startShake = false;
      shakeTimer = 0;
      Game::SetShake(0, 0);
    }
  }


  // Update valid game objects and delete those who aren't valid
  // if player is valid, else we would try to read players info
  if(player->isValid) {
    for(unsigned i=0; i<gameObjects.size(); ++i) {
      if(gameObjects[i]->isValid) {
        gameObjects[i]->Update();
      } else {
        delete gameObjects[i];
        gameObjects.erase(gameObjects.begin()+i);
      }
    }
  }



  // Spawn enemys!
  spawnEnemyTimer += 1;
  if (spawnEnemyTimer > 15) {
    // Random starting point on x axis
    int xpoint = ((rand() % Game::GetWidth()) + 1);
    gameObjects.push_back(new Enemy(xpoint, Game::GetHeight(), player));
    spawnEnemyTimer = 0;
  }

  // Update in-game timer
  if (startGameTimer) {
    elapsedTime = SDL_GetTicks() - gameStartTime;

    Milliseconds = elapsedTime;
    Seconds = elapsedTime / 1000;
    Minutes = Seconds / 60;

    TimerStringStream << std::setfill('0') << std::setw(2) << Minutes%60 << ":" <<
                        std::setfill('0') << std::setw(2) << Seconds%60 << ":" <<
                        std::setfill('0') << std::setw(3)  << Milliseconds%1000 << std::endl;

  }

}

void InGame::Render() {

  if(introStartTime == 0)
    introStartTime = SDL_GetTicks();

  switch (CurrentState) {
    case COUNTDOWN:
    {
      elapsedTime = SDL_GetTicks() - introStartTime;

      // Show each number ~half a second
      if(elapsedTime > 500) {
        introNumberIndex++;
        introStartTime = 0;
      }

      // Use enum values for your cases like case FIRST_INTRO instead of hard coding 0
      // Also case 0-3 are almost identical, I think you can extract to a function and pass slightly different values
      switch (introNumberIndex) {
        case 0: Game::RenderTexture(one->GetTexture(), Game::GetWidth()/2 - one->GetMidPointX(), Game::GetHeight()/2 - one->GetMidPointY());
                break;
        case 1: Game::RenderTexture(two->GetTexture(), Game::GetWidth()/2 - two->GetMidPointX(), Game::GetHeight()/2 - two->GetMidPointY());
                break;
        case 2: Game::RenderTexture(three->GetTexture(), Game::GetWidth()/2 - three->GetMidPointX(), Game::GetHeight()/2 - three->GetMidPointY());
                break;
        case 3: Game::RenderTexture(go->GetTexture(), Game::GetWidth()/2 - go->GetMidPointX(), Game::GetHeight()/2 - go->GetMidPointY());
                break;
        case 4: CurrentState = GAMEPLAY;
                introNumberIndex = 0;
                introStartTime = 0;
                Game::SetShake(0, 0);
                // Update player to avoid player flashing in the "wrong" position on screen
                player->Update();
                break;
      }
      break;
    }
    case GAMEPLAY:
    {
      Game::PlayMusic();

      for(auto obj : gameObjects)
        if(obj->isValid)
          obj->Render();


      // This is not a good way of rendering fast changeing textures.
      // Now we delete the texture and create a new one every rendering
      // frame. Don't do this at home kids!
      // With a Font atlas we could just change out the numbers from an
      // already loaded texture instead of rendering new ones.

      // It could also be improved by using SDL_TEXTUREACCESS_STREAMING
      // for SDL_CreateTexture. May adapt this when this gets prioritized

      // See also, SDL_Font Cache project

      // That being said.. this is how we do it here :>

      // Also you could extract text related things to it's own class so you don't
      // need code to load fonts in all places you render text

      if(inGameTimer)
        delete inGameTimer;

      inGameTimer = new Sprite(Game::CreateText(TimerStringStream.str(), "AldotheApache.ttf", color, 28, TTF_STYLE_ITALIC));
      Game::RenderTexture(inGameTimer->GetTexture(), Game::GetWidth() - inGameTimer->GetWidth() - 15, 10);
      TimerStringStream.str(std::string()); // Empty string stream

      if(inGameHighScore)
        delete inGameHighScore;

      std::string highscore = "HIGHSCORE: " + std::to_string(Game::GetHighScore());
      inGameHighScore = new Sprite(Game::CreateText(highscore, "AldotheApache.ttf", color, 42));
      Game::RenderTexture(inGameHighScore->GetTexture(), Game::GetWidth()/2 - inGameHighScore->GetMidPointX(), 10);
      break;
    }

    case GAMEOVER:
    {
      Game::SetRenderColor({0, 0, 0, 255});
      Game::ClearScreen();

      std::string highscorestring = "With a highscore of: " + std::to_string(Game::GetHighScore());
      if(totalScoreText)
        delete totalScoreText;

      totalScoreText = new Sprite(Game::CreateText(highscorestring, "AldotheApache.ttf", color, 22));

      Game::RenderTexture(titleText->GetTexture(), Game::GetWidth()/2 - titleText->GetMidPointX() ,150);
      Game::RenderTexture(totalScoreText->GetTexture(), Game::GetWidth()/2 - totalScoreText->GetMidPointX() ,200);
      Game::RenderTexture(infoText->GetTexture(), Game::GetWidth()/2 - infoText->GetMidPointX() ,400);
      break;
    }

    case MENU:
    {

      Game::RenderTexture(titleimage->GetTexture(), CenterOfScreen - (titleimage->GetWidth()*4)/2, 0, 4.0f);

      switch (GUI::Button(continueButtonSprite->GetTexture(), continueButtonSprite->GetClip(), CenterOfScreen, 400, b1Size)) {
        case BUTTON_IDLE: b1Size = 3.0f; break;
        case BUTTON_HOVER: b1Size = 3.5f; break;
        case BUTTON_PRESSED: b1Size = 3.5f; break;
        case BUTTON_RELEASED: {
          b1Size = 3.5f;
          CurrentState = GAMEPLAY;
          SDL_ShowCursor(SDL_DISABLE);
          Game::SetMouse(mx,my);
          break;
        }
      }

      switch (GUI::Button(exitButtonSprite->GetTexture(), exitButtonSprite->GetClip(), CenterOfScreen, 500, b3Size)) {
        case BUTTON_IDLE: b3Size = 3.0f; break;
        case BUTTON_HOVER: b3Size = 3.5f; break;
        case BUTTON_PRESSED: b3Size = 3.5f; break;
        case BUTTON_RELEASED: b3Size = 3.5f; Game::SetNextState( STATE_EXIT ); break;
      }


      break;
    }
  }


}
