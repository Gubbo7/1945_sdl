#ifndef RENDERER_H
#define RENDERER_H
#include "common.h"

int RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, point* p, size* s);
SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file);
SDL_Rect* NewRect(point* p, size* s);
void CloseWindow(SDL_Renderer* r, SDL_Window* win);

// int SpriteSheetRendering(SDL_Renderer* r, SDL_Texture* img, Uint64* ticks, int sprites, point srcP, point dstP, size srcS, size dstS );
// SDL_Texture* NewSpriteSheet(SDL_Renderer* renderer, char* path_file);

#endif //RENDERER_H