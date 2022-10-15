#include "CreditState.hpp"

CreditState::CreditState() {
  centerOfscreen = Game::GetWidth()/2;

  std::string font = "Quicksand-Bold.ttf";
  int fontSize = 22;

  TitleText = new Sprite(Game::CreateText("CREDITS!","AldotheApache.ttf", color,132));

  TextRad1 = new Sprite(Game::CreateText("Code & Graphics:  z13swee (Sebastian Ekman)",font, color, fontSize));
  TextRad2 = new Sprite(Game::CreateText("Sound Effects:  Unknown",font, color, fontSize));
  TextRad3 = new Sprite(Game::CreateText("Music:  Flavio Concini, andrew-paglinawan",font, color, fontSize));
  TextRad4 = new Sprite(Game::CreateText("Font:  AJ Paglia",font, color, fontSize));

  TextRad5 = new Sprite(Game::CreateText("This game is a clone of the game Dodge made",font, color, fontSize));
  TextRad6 = new Sprite(Game::CreateText("by Eddy Rashed and Oskar Zanota and was", font, color, fontSize));
  TextRad7 = new Sprite(Game::CreateText("built for the great community of Linux users! :)",font, color, fontSize));

  TextRad8 = new Sprite(Game::CreateText("Thanks for playing!",font, color,28));
}

CreditState::~CreditState() {

}

void CreditState::HandleEvents() {

  while( SDL_PollEvent( &event ) )
  {

      if( event.type == SDL_QUIT )
      {
          //Quit the program
          Game::SetNextState( STATE_EXIT );
      }
      else if( ( event.type == SDL_KEYDOWN ))
      {
        Game::ClearScreen();

        switch (event.key.keysym.sym){
          case SDLK_ESCAPE:
            Game::SetNextState( STATE_INTRO );
            break;
          default:
            Game::SetNextState( STATE_INTRO );
            break;
        }
      }
  }
}
void CreditState::Update() {

}

void CreditState::Render() {

  Game::SetRenderColor({0,0,0,200});

  Game::SetRenderColor({255,255,255,255});
  Game::RenderTexture(TitleText->GetTexture(), centerOfscreen - TitleText->GetMidPointX(), 20);

  Game::RenderTexture(TextRad1->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 200);
  Game::RenderTexture(TextRad2->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 230);
  Game::RenderTexture(TextRad3->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 260);
  Game::RenderTexture(TextRad4->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 290);

  Game::RenderTexture(TextRad5->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 360);
  Game::RenderTexture(TextRad6->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 390);
  Game::RenderTexture(TextRad7->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 420);

  Game::RenderTexture(TextRad8->GetTexture(), centerOfscreen - TextRad1->GetMidPointX(), 490);

}
