//Per dire a SDL che si usera' il proprio main applicativo.
//Altrimenti SDL cerca di caricare il main da SDL2Main.lib
//NOTA: Si può passare anche come argomento di compilazione con -D
#define SDL_MAIN_HANDLED
#include "common.h"
#include "renderer.h"
#include "gameobj.h"


int main() {
    SDL_Init(SDL_INIT_VIDEO);

    size windowSize = NewSize(640, 480);

    SDL_Window* window = SDL_CreateWindow(
        "1945",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowSize.Width,
        windowSize.Height,
        0
    );

    if (window == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        return 2;
    }

    GameObject go;
    NewGameObj(&go, NewPoint(10,10),NewSize(50,50),"assets/ui/life.png");

    

    SDL_Texture* texture = NewTexture(renderer, "assets/player/bullet.png");

    SDL_Rect* texture_rect;

    Uint64 curr_count = SDL_GetPerformanceCounter();
    Uint64 last_count = curr_count;
    float delta_time = 0.f;
    
    char title[100];
    float update_time = 0.f;
    float time_counter = 0.f;

    boolean done = false;   
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
        }

        last_count = curr_count;
        curr_count = SDL_GetPerformanceCounter();
        delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1.f / delta_time);

        update_time += delta_time;
        if (update_time >= 1.f) {
            update_time -= 1.f;
            sprintf_s(title, sizeof(title), "Delta Time: %.6f - Fps: %d", delta_time, fps);
            SDL_SetWindowTitle(window, title);
        }

        RendererGameobject(renderer, &go);

        // Blit
        SDL_RenderPresent(renderer);
    }

    //Clean Up
    CloseWindow(renderer, window);

    return 0;
}