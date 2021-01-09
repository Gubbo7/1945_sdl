#include "renderer.h"

int RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, point* p, size* s){
    SDL_Rect* rect = NewRect(p, s);
    int result = SDL_RenderCopy(r, tex, NULL, rect);
    free(rect);
    return result;
}

SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file){
    return (SDL_Texture*)IMG_LoadTexture(renderer, path_file); 
}

SDL_Rect* NewRect(point* p, size* s){
    SDL_Rect* rect = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
    rect->x = p->x;
    rect->y = p->y; 
    rect->w = s->Width; 
    rect->h = s->Height;
    return rect;
}

// int SpriteSheetRendering(SDL_Renderer* r, SDL_Texture* img, Uint64* ticks, int sprites, point srcP, point dstP, size srcS, size dstS ){
//     Uint64 tenths = *ticks / 150; // secondi
//     Uint64 sprite = tenths % sprites;
    
//     SDL_Rect src;
//     NewRectFloat(&src,srcP.x * sprite,srcP.y,srcS.Width,srcS.Height);
    
//     SDL_Rect dst;
//     NewRectFloat(&dst,dstP.x,dstP.y,dstS.Width,dstS.Height);
    
//     return SDL_RenderCopy(r, img, &src, &dst);
// }

// SDL_Texture* NewSpriteSheet(SDL_Renderer* renderer, char* path_file){
//     return IMG_LoadTexture(renderer, path_file);
// }



void CloseWindow(SDL_Renderer* r, SDL_Window* win){
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

