#include "character.h"

Character* NewCharacter(point* p, size* s, int hp, float speed, char* path){
    Character* c = (Character*)calloc(1, sizeof(Character));
    c->hp = hp;
    c->speed = speed;
    c->go = NewGameObj(p, s, path);
    return c;
}

void RenderCharacter(SDL_Renderer* renderer, Character* c){
    RenderGameobject(renderer, c->go);
}

// void DeathAnimChar(SDL_Renderer* renderer, char* path){
//     NewSpriteSheet(renderer, path);
// }

void DestroyCharacter(Character* c){
    DestroyGameObj(c->go);
    free(c);
}