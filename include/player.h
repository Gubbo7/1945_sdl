#ifndef PLAYER_H
#define PLAYER_H

#include "character.h"
#include "inputsys.h"
#include "ui.h"
#include "ttf.h"

typedef struct {
    Character* character;
    int lives;
    boolean isAlive;
    boolean isDead;
    GameObject* life1;
    GameObject* life2;
    GameObject* life3;
    Input* input;
    Font* font;
    Mix_Chunk* explosion;
    int score;
} Player;

Player* NewPlayer(point* p, size* s, Input* input, int hp, float speed, char* path);
//void RenderPlayer(SDL_Renderer* renderer, Player* player, double deltaTime);
boolean UpdatePlayer(SDL_Renderer* renderer, SDL_Event* event, Player* player, double deltaTime);
void DestroyPlayer(Player* p);

#endif 