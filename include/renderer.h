#ifndef RENDERER_H
#define RENDERER_H
#include "common.h"

typedef struct 
{
    List* animations;
} Animator;

typedef struct 
{
    char* name;
    int totFrames;
    int currFrame;
    char* texture_path;
    double timeFrame;
    double delayFrame;
    size* frameSize;
    List* list;
} Animation;

//TEXTURE
int RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, point* p, size* s);
int RenderingPath(SDL_Renderer*, char*, point*, size*);
SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file);
SDL_Rect* NewRect(point* p, size* s);
void DestroyRect(SDL_Rect* rect);

//ANIM
Animator* NewAnimator();
Animation* NewAnimation(char*, char*, SDL_Rect*, int, double);
void DestroyAnimator(Animator*);
void DestroyListAnimation(List*);
void DestroyAnimation(Animation*);

boolean RenderingThisAnimation(SDL_Renderer*, Animator*, char*, point*, double);
boolean RenderingListAnimation(SDL_Renderer*, Animation*, SDL_Rect*, double);
void RenderingAnimation(SDL_Renderer*, char*, SDL_Rect*, SDL_Rect*);


void CloseWindow(SDL_Renderer* r, SDL_Window* win);


#endif //RENDERER_H