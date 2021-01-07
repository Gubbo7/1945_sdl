#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobj.h"
#include "renderer.h"

typedef struct {
    GameObject go;
    int hp;
    float speed;
    char* path;
} Character;

void NewCharacter(Character* c, point p, size s, int hp, float speed, char* path);
void RenderingCharacter(SDL_Renderer* renderer, Character* c);



#endif //CHARACTER_H