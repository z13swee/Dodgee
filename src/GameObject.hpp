#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

struct ivec2 {
  int x;
  int y;
};

// Simple base class
class GameObject
{
  public:
    bool isValid = true;
    bool isCollidable = false;
    ivec2 position = { 0,0 };
    SDL_Rect collisionBox { 0,0,0,0 };

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

    virtual ~GameObject() {}

  private:

};

#endif
