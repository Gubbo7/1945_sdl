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
#include "player.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    size* windowSize = NewSize(640, 480);

    SDL_Window* window = SDL_CreateWindow(
        "1945",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        windowSize->Width,
        windowSize->Height,
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

    //Player
    Player* player = NewPlayer(NewPoint(290,180), NewSize(50,50), 100, 1000, "./assets/ui/life.png");

    //Input
    Input* input = InitInputSystem("WASD");

    //Bullet List
    List* bullets = NewList();
    AddGoToList(bullets, 10, "bullet", playerBullet);

    //UI
    GameObject* life1 = NewGameObj(NewPoint(100,HEIGHT_WINDOW-73), NewSize(40, 40), "./assets/ui/life.png");
    GameObject* life2 = NewGameObj(NewPoint(55,HEIGHT_WINDOW-73), NewSize(40, 40), "./assets/ui/life.png");
    GameObject* life3 = NewGameObj(NewPoint(10,HEIGHT_WINDOW-73), NewSize(40, 40), "./assets/ui/life.png");

    GameObject* ui_bottom = NewGameObj(NewPoint(0,HEIGHT_WINDOW-74), NewSize(WIDTH_WINDOW, 75), "./assets/ui/bottom.png");
    GameObject* background = NewGameObj(NewPoint(0, 0), NewSize(640, 405), "./assets/map/water2.png");

    //island
    List* islands = NewList();
    AddGoToList(islands, 1, "island", Normal);
    AddGoToList(islands, 1, "island", Vulcan);
    AddGoToList(islands, 1, "island", Sand);


    List* water = NewList();
    AddGoToList(water, 1, "background", 0);

    Uint64 curr_count = SDL_GetPerformanceCounter();
    Uint64 last_count = curr_count;
    double delta_time = 0.f;
    double delay = 0.f;
    
    char title[100];
    float update_time = 0.f;
    float time_counter = 0.f;
    double delayPlayer = 0;

    boolean done = false;   
    while (!done) {
        SDL_RenderClear(renderer);
        SDL_Event event;

        Uint64 ticks = SDL_GetTicks();

        last_count = curr_count;
        curr_count = SDL_GetPerformanceCounter();
        delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1.f / delta_time);

        

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
            if(player->isAlive)
                MoveInput(&event, input, player, &delta_time, bullets);
            
            
        }

        if(!player->isAlive){
            delay += delta_time;
            PlayerDied(player, &delay, delayPlayer);
        }
        
        update_time += delta_time;
        if (update_time >= 1.f) {
            update_time -= 1.f;
            sprintf_s(title, sizeof(title), "Delta Time: %.6f - Fps: %d", delta_time, fps);
            SDL_SetWindowTitle(window, title);
        }

        RenderGOList(renderer, water, true, delta_time);
        RenderGOList(renderer, islands, false, delta_time);

        RenderingBullets(renderer, bullets, delta_time);
        
        RenderPlayer(renderer, player);

        // UI BASE
        RenderGameobject(renderer, ui_bottom);

        // LIFES
        RenderGameobject(renderer, life1);
        RenderGameobject(renderer, life2);
        RenderGameobject(renderer, life3);
        
        // Clear
        //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        //SDL_RenderClear(renderer);
        
        // Blit
        //SDL_UpperBlit(&background->Surface_, , window, win);
        //SDL_UpdateWindowSurface(window);
        SDL_RenderPresent(renderer);
    }

    //Clean Up
    CloseWindow(renderer, window);

    DestroyGameObj(life1);
    DestroyGameObj(life2);
    DestroyGameObj(life3);
    DestroyGameObj(ui_bottom);
    DestroyGameObj(background);

    DestroyList(bullets);
    DestroyPlayer(player);
    DestroyInput(input);

    return 0;
}