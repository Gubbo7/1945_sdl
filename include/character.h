#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobj.h"

typedef struct {
    GameObject* go;
    int hp;
    float speed;
} Character;

Character* NewCharacter(point* p, size* s, int hp, float speed, char* path);
void RenderCharacter(SDL_Renderer* renderer, Character* c);
//void DeathAnimChar();
void DestroyCharacter(Character* c);

#endif //CHARACTER_H