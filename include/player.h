#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"

typedef struct {
    Character* character;
    int lives;
    boolean isAlive;
} Player;

Player* NewPlayer(point* p, size* s, int hp, float speed, char* path);
void RenderPlayer(SDL_Renderer* renderer, Player* player);
void PlayerDied(Player* player, double* deltaTime, double delay);
void DestroyPlayer(Player* p);

#endif 