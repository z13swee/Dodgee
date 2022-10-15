#include "Effects.hpp"

SimpleExplosion::SimpleExplosion(int x, int y) {
    orgRenderColor = Game::GetRenderColor();

    debrieSize = 10;
    totalDebries = 6;
    speed = 6.5;
    lifetime = 80;
    life = 0;

    for(int i=0; i<=totalDebries; i++)
        debrie.push_back({x,y,debrieSize,debrieSize});
}

void SimpleExplosion::HandleEvents() {
}

void SimpleExplosion::Update() {
    life += 1.0f;

    for(int i=0; i<=totalDebries; i++) {
        auto theta = ((3.14f*2) / totalDebries);
        auto angle = theta * i;

        debrie[i].x += speed*cos(angle);
        debrie[i].y += speed*sin(angle);

        debrie[i].w -= (lifetime-life)*.01;
        debrie[i].h -= (lifetime-life)*.01;
    }

    if(life >= lifetime)
        isValid = false;

}

void SimpleExplosion::Render() {

    Game::SetRenderColor({255, 255, 255, 255});
    for(auto deb : debrie)
        Game::RenderFilledRect(&deb);
    Game::SetRenderColor(orgRenderColor);

}
