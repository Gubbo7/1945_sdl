#ifndef CHARACTER_H
#define CHARACTER_H

#include "gameobj.h"
#include "bullet.h"

typedef struct {
    double hp;
    float speed;
    List* bullets;
    GameObject* go;
    Animator* animator;
} Character;

Character* NewCharacter(point* p, size* s, int hp, float speed, char* path);
void UpdateCharacter(SDL_Renderer* renderer, Character* c, double deltatime);
void AddAnimation(Character* c, char* animationName, char* textureName, SDL_Rect* rect, int numFrame, double deltatime);
//void DeathAnimChar();
void DestroyCharacter(Character* c);

#endif //CHARACTER_H