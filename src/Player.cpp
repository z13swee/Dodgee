#include "Player.hpp"

Player::Player() {
  isCollidable = true;

  playerSprite = Game::CreateTexture("player.png");

  for(int i=0; i<=3; i++)
    trailTextures[i] = Game::CreateTexture("player_trail.png");

  // Get newest mouse position and update history
  SDL_GetMouseState(&position.x, &position.y);

  // Setup for trail positions
  for(int i=0; i<=3; i++)
    positionHistory[i] = {position.x, position.y};

  //Set collision box dimension
  collisionBox.x = position.x;
  collisionBox.y = position.y;
  collisionBox.w = 8;
  collisionBox.h = 8;
}

Player::~Player() {

  SDL_DestroyTexture(playerSprite);

  // Only need to destroy at index 0 becuse the rest
  // is the same texture (given by Game::CreateTexture)
  SDL_DestroyTexture(trailTextures[0]);
}


void Player::HandleEvents() {};


void Player::Update() {
  SDL_GetMouseState(&position.x, &position.y);

  // Update Colliderbox
  collisionBox.x = position.x+8;
  collisionBox.y = position.y+8;

  if(historyIndex >= 4)
    historyIndex = 0;

  positionHistory[historyIndex] = {position.x, position.y};
  historyIndex++;
}

void Player::Render() {

  for(int i=0; i<=3; i++)
    Game::RenderTexture(trailTextures[i], positionHistory[i].x, positionHistory[i].y);

  Game::RenderTexture(playerSprite, position.x, position.y);


}
