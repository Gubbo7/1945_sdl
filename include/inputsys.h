#ifndef INPUTSYS_H
#define INPUTSYS_H

#include "common.h"
#include "list.h"
#include "player.h"

typedef struct{
    boolean isActive;
    SDL_Scancode up;
    SDL_Scancode down;
    SDL_Scancode left;
    SDL_Scancode right;
    SDL_Scancode shoot;

} Input;



void InitButton(Input* input, char* movement);
Input* InitInputSystem(char* buttons);
void MoveInput(SDL_Event* event, Input* inputSys, Player* player, double* deltaTime, List* bullets);
void Shoot(Character* c, double* deltaTime, List* bullletList);

void DestroyInput(Input* input);

#endif //INPUTSYS_H