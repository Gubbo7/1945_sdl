#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "common.h"
#include "renderer.h"

typedef struct{
    point position;
    size t_size;
    char* t_path;
} GameObject;

void NewGameObj(GameObject* go, point p, size t_size, char* t_path);
void RendererGameobject(SDL_Renderer* r, GameObject* go);
void RendererGameobjectWithAnimation(SDL_Renderer* r, GameObject* go, int numFrame);

#endif //GAMEOBJ_H