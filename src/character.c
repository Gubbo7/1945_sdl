#include "character.h"

Character* NewCharacter(point* p, size* s, int hp, float speed, char* path){
    Character* c = (Character*)calloc(1, sizeof(Character));
    c->hp = hp;
    c->speed = speed;
    c->bullets = NewList();
    c->go = NewGameObj(p, s, path);
    c->animator = NewAnimator();
    return c;
}

void AddAnimation(Character* c, char* animationName, char* textureName, SDL_Rect* rect, int frames, double timeFrame){
    AddToList(c->animator->animations, NewAnimation(animationName, textureName, rect, frames, timeFrame));
}

void UpdateCharacter(SDL_Renderer* render, Character* c, double deltaTime){
    if (c->go->isActive)
    {
        RenderingThisAnimation(render, c->animator, (char*)"main", c->go->position, deltaTime);
    }
}


// void DeathAnimChar(SDL_Renderer* renderer, char* path){
//     NewSpriteSheet(renderer, path);
// }

void DestroyCharacter(Character* c){
    DestroyGameObj(c->go);
    DestroyList(c->bullets);
    DestroyAnimator(c->animator);
    free(c);
}