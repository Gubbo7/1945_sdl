#include "gameobj.h"

void NewGameObj(GameObject* gameobj, point p, size size, char* t_path){
    gameobj->position = p;
    gameobj->t_path = t_path;
    gameobj->t_size = size;
}

void RendererGameobject(SDL_Renderer* r, GameObject* go){
    SDL_Texture* texture = NewTexture(r, go->t_path);
    RenderingTexture(r, texture, go->rect);
}