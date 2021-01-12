//Per dire a SDL che si usera' il proprio main applicativo.
//Altrimenti SDL cerca di caricare il main da SDL2Main.lib
//NOTA: Si può passare anche come argomento di compilazione con -D
#define SDL_MAIN_HANDLED
#include "player.h"
#include "enemy.h"
#include "ui.h"
#include "physics.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Init(SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

    if(TTF_Init()){
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not initialize font: %s\n", SDL_GetError());
        return 1;
    }

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

    SDL_Surface* favicon = IMG_Load("./assets/extra/icon.png");
    SDL_SetWindowIcon(window, favicon);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Could not create renderer: %s\n", SDL_GetError());
        return 2;
    }


    Uint64 curr_count = SDL_GetPerformanceCounter();
    Uint64 last_count = curr_count;
    double delta_time = 0.f;
    
    char title[100];
    float update_time = 0.f;

    boolean done = false;


    //Player
    Player* player = NewPlayer(NewPoint(290,180), NewSize(65,65), InitInputSystem("WASD"),100, 1000, "./assets/player/myplane_strip3.png");

    //Enemy
    EnemyManager* enemymgr = NewEnemyManager();
    AddEnemyManagerList(enemymgr, NewSize(32,32), "./assets/enemy/enemy1_strip3.png", 5);
    AddEnemyManagerList(enemymgr, NewSize(32,32), "./assets/enemy/enemy2_strip3.png", 2);
    AddEnemyManagerList(enemymgr, NewSize(32,32), "./assets/enemy/enemy3_strip3.png", 10);

    PhysicsManager* physicsManager = NewPhysicsManager(player, enemymgr);

    //island
    List* islands = NewList();
    AddGoToList(islands, 2, "island", Normal);
    AddGoToList(islands, 2, "island", Vulcan);
    AddGoToList(islands, 2, "island", Sand);

    Interface* ui = NewInterface();
    AddUIList(ui, NewPoint(0,HEIGHT_WINDOW-74), NewSize(WIDTH_WINDOW, 75), "./assets/ui/bottom.png");

    List* water = NewList();
    AddGoToList(water, 2, "background", 0);

    Mix_Music* soundTrack = Mix_LoadMUS("./assets/audio/background.mp3");
    Mix_AllocateChannels(2);
    
    Mix_VolumeMusic(SDL_MIX_MAXVOLUME/20);
    Mix_PlayMusic(soundTrack, -1);
    
    SDL_Event* event = (SDL_Event*)calloc(1, sizeof(SDL_Event));
    while (!done) {
        SDL_RenderFlush(renderer);
        SDL_RenderClear(renderer);

        // DELTATIME
        last_count = curr_count;
        curr_count = SDL_GetPerformanceCounter();
        delta_time = (float)(curr_count - last_count) / (float)SDL_GetPerformanceFrequency();
        int fps = (int)(1.f / delta_time);

        update_time += delta_time;
        if (update_time >= 1.f) {
            update_time -= 1.f;
            sprintf_s(title, sizeof(title), "1945\n Delta Time: %.6f - Fps: %d", delta_time, fps);
            SDL_SetWindowTitle(window, title);
        }
        
        // BACKGROUND
        RenderGOList(renderer, water, true, delta_time);
        RenderGOList(renderer, islands, false, delta_time);

        // PHYSICS
        CheckCollision(physicsManager);

        // ENEMY
        UpdateEnemyManager(renderer, enemymgr, delta_time);

        // UI BASE
        UpdateInterface(renderer, ui, delta_time);

        // PLAYER (INPUT, BULLETS, LIFE MANAGER)
        done = UpdatePlayer(renderer, event, player, delta_time);

        // BLIT
        SDL_RenderPresent(renderer);
    }

    //CLEAN UP
    CloseWindow(renderer, window);
    SDL_FreeSurface(favicon);
    DestroyPlayer(player);
    DestroyEnemyManager(enemymgr);
    DestroyPhysicsManager(physicsManager);
    DestroyInterface(ui);
    DestroyList(islands);
    DestroyList(water);

    Mix_FreeMusic(soundTrack);
    Mix_CloseAudio();
    
    return 0;
}