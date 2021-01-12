#ifndef UI_H
#define UI_H

#include "common.h"
#include "renderer.h"


typedef struct 
{
    List* UIList;
} Interface;

typedef struct 
{
    char* path;
    point* position;
    size*  size;
} UI;

Interface* NewInterface();
void AddUIList(Interface*, point*, size*, char*);
void DestroyInterface(Interface* i);
void UpdateInterface(SDL_Renderer*, Interface*, double dt);

UI* NewUI(point*, size*, char*);
void RenderingUI(SDL_Renderer* renderer, UI* ui);
void DestroyUI(UI* ui);
void DestroyInterface(Interface* i);

#endif // UI_H
