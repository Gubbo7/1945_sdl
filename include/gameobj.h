#ifndef GAMEOBJ_H
#define GAMEOBJ_H

#include "common.h"
#include "renderer.h"

typedef struct{
    point* position;
    size* t_size;
    char* t_path;
    boolean isActive;
} GameObject;

enum IslandsType{Normal = 0, Vulcan, Sand};
typedef enum IslandsType_ IslandsType;

GameObject* NewIsland(IslandsType it);
void RenderGOList(SDL_Renderer* renderer, List* goList, boolean bg, float deltaTime);
void RenderGOActive(SDL_Renderer* renderer, GameObject* go, boolean bg);

GameObject* NewGameObj(point* p, size* t_size, char* t_path);
void RenderGameobject(SDL_Renderer* r, GameObject* go);

void AddGoToList(List*, int, char*, int);

void DestroyGameObj(GameObject*);





#endif //GAMEOBJ_H