#ifndef INPUTSYS_H
#define INPUTSYS_H

#include "common.h"
#include "list.h"
#include "character.h"

typedef struct{
    boolean isActive;
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode shoot;
    Mix_Chunk* explosion;

} Input;



Input* InitInputSystem(char* buttons);
void InitButton(Input* input, char* movement);
void MoveInput(SDL_Event* event, Input* inputSys, Character* c, double deltaTime);
void Shoot(Character* c);
boolean UpdateInput(SDL_Event*, Input* input, Character* c, double deltaTime);

void DestroyInput(Input* input);

#endif //INPUTSYS_H