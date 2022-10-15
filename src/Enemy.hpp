#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <memory>
#include "Game.hpp"

class Enemy : public GameObject
{
  public:
    Enemy(int x, int y, GameObject* target);
    ~Enemy();

    void HandleEvents();
    void Update();
    void Render();

  private:
    Sprite* enemySprite = nullptr;

    float speed = 1.0f;
    float rndAcc = (float)((rand() % 5) + 1)/10;
    int rndMaxAcc = (rand() & 5)+10;

    float myVelX = 0.0;
    float myVelY = 0.0;
    float MAX_Accel = 5; //10 funkar bra också

    float AccelerationX = rndAcc; //0.2;
    float AccelerationY = rndAcc; //0.2;

    GameObject* Target = nullptr;
};

#endif
