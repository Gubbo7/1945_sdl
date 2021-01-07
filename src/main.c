//Per dire a SDL che si usera' il proprio main applicativo.
//Altrimenti SDL cerca di caricare il main da SDL2Main.lib
//NOTA: Si può passare anche come argomento di compilazione con -D
#define SDL_MAIN_HANDLED
#include "common.h"
#include "renderer.h"
#include "gameobj.h"
#include "character.h"
#include "inputsys.h"
#include "bullet.h"


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

    Character player;
    NewCharacter(&player, NewPoint(290,202),NewSize(60,60), 100, 5000, "assets/ui/life.png");
    
    List* bulletList = NewList();
    Bullet bullet0 = NewBullet(playerBullet);
    Bullet bullet1 = NewBullet(playerBullet);
    Bullet bullet2 = NewBullet(playerBullet);
    Bullet bullet3 = NewBullet(playerBullet);
    Bullet bullet4 = NewBullet(playerBullet);
    Bullet bullet5 = NewBullet(playerBullet);

    AddToList(bulletList, &bullet0);
    AddToList(bulletList, &bullet1);
    AddToList(bulletList, &bullet2);
    AddToList(bulletList, &bullet3);
    AddToList(bulletList, &bullet4);
    AddToList(bulletList, &bullet5);

    Input input;
    InitInputSystem(&input, "WASD");
    
    //ui
    SDL_Texture* textureUI = NewTexture(renderer, "assets/ui/bottom.png");
    SDL_Texture* textureLife = NewTexture(renderer, "assets/ui/life.png");

    Uint64 curr_count = SDL_GetPerformanceCounter();
    Uint64 last_count = curr_count;
    double delta_time = 0.f;
    double delay = 0.f;
    
    char title[100];
    float update_time = 0.f;
    float time_counter = 0.f;

    boolean done = false;   
    while (!done) {
        SDL_RenderClear(renderer);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
            MoveInput(renderer, &event, &input, &player, &windowSize, &delta_time, bulletList);
            //Shoot(renderer, &player, &windowSize, &delta_time, bulletList);
        }

        last_count = curr_count;
        curr_count = SDL_GetPerformanceCounter();
        delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1.f / delta_time);

        delay += delta_time;

        update_time += delta_time;
        if (update_time >= 1.f) {
            update_time -= 1.f;
            sprintf_s(title, sizeof(title), "Delta Time: %.6f - Fps: %d", delta_time, fps);
            SDL_SetWindowTitle(window, title);
        }

        RenderingBullets(renderer, bulletList, delta_time);

        RenderingCharacter(renderer, &player);
      
        // //UI
        RenderingTexture(renderer, textureUI, NewPoint(0, windowSize.Height-74), NewSize(windowSize.Width, 75));
        RenderingTexture(renderer, textureLife, NewPoint(10, windowSize.Height-72), NewSize(40, 40));
        RenderingTexture(renderer, textureLife, NewPoint(55, windowSize.Height-72), NewSize(40, 40));
        RenderingTexture(renderer, textureLife, NewPoint(100, windowSize.Height-72), NewSize(40, 40));

        // Blit
        SDL_RenderPresent(renderer);
        
    }

    //Clean Up
    CloseWindow(renderer, window);
    DestroyList(bulletList);
    // free(&input);
    // free(&player);
    // free(&window);

    return 0;
}