#ifndef RENDERER_H
#define RENDERER_H
#include "common.h"

void RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, SDL_Rect* rect);
SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file);
void NewRect(SDL_Rect* rect, point p, size w);
void NewRectFloat(SDL_Rect* rect,float x, float y, float width, float height);
void CloseWindow(SDL_Renderer* r, SDL_Window* win);


#endif //RENDERER_H