#include "renderer.h"

int RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, point p, size s){
    SDL_Rect rect;
    NewRect(&rect, p, s);
    return SDL_RenderCopy(r, tex, NULL, &rect);
}

SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file){
    return (SDL_Texture*)IMG_LoadTexture(renderer, path_file); 
}

void NewRect(SDL_Rect* rect, point p, size w){
    rect->x = p.x;
    rect->y = p.y; 
    rect->w = w.Width; 
    rect->h = w.Height;
}

void NewRectFloat(SDL_Rect* rect, float x, float y, float width, float height){
    rect->x = x;
    rect->y = y; 
    rect->w = width; 
    rect->h = height;
}

void CloseWindow(SDL_Renderer* r, SDL_Window* win){
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

