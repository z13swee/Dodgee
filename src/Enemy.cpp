#include "Enemy.hpp"

Enemy::Enemy(int _x, int _y, GameObject* _target) {
  isCollidable = true;

  if(_target != nullptr)
    Target = _target;

  enemySprite = new Sprite(Game::CreateTexture("kub1.png"));

  position.x = _x;
  position.y = _y;

  collisionBox.w = enemySprite->GetWidth();
  collisionBox.h = enemySprite->GetHeight();

}
Enemy::~Enemy() {
  delete enemySprite;
}

void Enemy::HandleEvents() {};

void Enemy::Update() {

  if(!Target)
    return;

  if(position.x > Target->position.x) {
    myVelX -= AccelerationX;
  } else {
    myVelX += AccelerationX;
  }

  if(position.y > Target->position.y) {
    myVelY -= AccelerationY;
  } else {
    myVelY += AccelerationY;
  }

  // CAP x accel
  if(abs(myVelX) > MAX_Accel) {
    if(myVelX > 0) {
      myVelX = MAX_Accel;
    } else {
      myVelX = -MAX_Accel;
    }
  }

  // CAP y accel
  if(abs(myVelY) > MAX_Accel) {
    if(myVelY > 0) {
      myVelY = MAX_Accel;
    } else {
      myVelY = -MAX_Accel;
    }
  }

  position.x += speed*myVelX;
  position.y += speed*myVelY;

  // Move along the collision box
  collisionBox.x = position.x;
  collisionBox.y = position.y;


}

void Enemy::Render() {
  Game::RenderTexture(enemySprite->GetTexture(), *&position.x, *&position.y);
}
