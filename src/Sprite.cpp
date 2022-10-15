#include "Sprite.hpp"

Sprite::Sprite() {

}

Sprite::Sprite(SDL_Texture* texture) {
  if(texture != nullptr) {
    SourceTexture = texture;

    SDL_QueryTexture(SourceTexture, NULL, NULL, &Width, &Height);

    midPointX = Width / 2;
    midPointY = Height / 2;
  }
}

Sprite::Sprite(const std::string path) {
  SourceTexture = Game::CreateTexture(path);
  if(SourceTexture != nullptr) {
    SDL_QueryTexture(SourceTexture, NULL, NULL, &Width, &Height);

    midPointX = Width / 2;
    midPointY = Height / 2;
  }
}

Sprite::~Sprite() {
  SDL_DestroyTexture(SourceTexture);
}

void Sprite::SetClip(SDL_Rect _clip) {
  Clip = _clip;
}

void Sprite::SetColor(int r, int g, int b) {
  SDL_SetTextureColorMod(SourceTexture, r, g, b);
}

void Sprite::SetAlpha(int alpha) {
  SDL_SetTextureAlphaMod(SourceTexture, alpha);
}

SDL_Rect Sprite::GetClip() {
  return Clip;
}
SDL_Texture* Sprite::GetTexture() {
  return SourceTexture;
}
int Sprite::GetWidth() {
  return Width;
}
int Sprite::GetHeight() {
  return Height;
}
int Sprite::GetMidPointX() {
  return midPointX;
}
int Sprite::GetMidPointY() {
  return midPointY;
}
