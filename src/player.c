#include "player.h"

Player* NewPlayer(point* p, size* s, int hp, float speed, char* path){
    Player* player = (Player*)calloc(1, sizeof(Player));
    player->lives = 3;
    player->character = NewCharacter(p, s, hp, speed, path);
    player->isAlive = true;
    return player;
}

void RenderPlayer(SDL_Renderer* renderer, Player* player){
    RenderCharacter(renderer, player->character);
}

void PlayerDied(Player* player, double* deltaTime, double delay){
    
    delay += *deltaTime;
    if(player->character->hp <= 0){
        
        player->isAlive = false;
        if(delay >= 3){
            printf("morto");
            player->lives--;
            printf("%d ", player->lives);
            player->isAlive = true;
            *deltaTime = 0;
        }

    }
    
}

void DestroyPlayer(Player* p){
    DestroyCharacter(p->character);
    free(p);
}
