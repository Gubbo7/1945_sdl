#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "common.h"
#include "renderer.h"

typedef struct{
    point position;
    size t_size;
    char* t_path;
    SDL_Texture* texture;
    SDL_Rect* rect;
} GameObject;

void NewGameObj(GameObject* go, point p, size t_size, char* t_path);
void RendererGameobject(SDL_Renderer* r, GameObject* go);

#endif //GAMEOBJ_H