#ifndef INPUTSYS_H
#define INPUTSYS_H

#include "common.h"
#include "list.h"
#include "character.h"
#include "playerbullet.h"

typedef struct{
    boolean isActive;
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode shoot;

} Input;



void InitButton(Input* input, char* movement);
void InitInputSystem(Input* input, char* buttons);
void MoveInput(SDL_Renderer* renderer, SDL_Event* event, Input* inputSys, Character* c, size* size, double* deltaTime, List* bullets);
void Shoot(SDL_Renderer* renderer, Character* c, size* size, double* deltaTime, List* bullletList);


#endif //INPUTSYS_H