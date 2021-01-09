#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

typedef struct{
    Character* character;
} Enemy;

enum enemyType {enemyGreen, enemyOrange, enemyWhite, enemyBlue};
typedef enum enemyType EnemyType;

Enemy* NewEnemy(point* p, size* s, int hp, float speed, char* path);
void RenderEnemy(SDL_Renderer* renderer, Enemy* enemy);
void EnemyDie(Enemy* enemy);
void DestroyEnemy(Enemy* enemy);

#endif