#include "character.h"

void NewCharacter(Character* c, point p, size s, int hp, float speed, char* path){

    c->hp = hp;
    c->speed = speed;
    c->path = path;
    NewGameObj(&c->go, p, s, path);
}

void RenderingCharacter(SDL_Renderer* renderer, Character* c){
    RendererGameobject(renderer, &c->go);
}
