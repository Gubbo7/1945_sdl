#ifndef ENEMY_H
#define ENEMY_H

#include "character.h"

typedef struct
{
    Character* character;
    int score;
    float timeShoot;
    boolean isAlive;
    boolean isDead;
    Mix_Chunk* shoot;
    Mix_Chunk* explosion;
} Enemy;

typedef struct
{
    List* enemys;
} EnemyManager;


// ENEMY MANAGER
EnemyManager* NewEnemyManager();
void AddEnemyManagerList(EnemyManager*, size*, char*, int);
void UpdateEnemyManager(SDL_Renderer*, EnemyManager*, double);
void DestroyEnemyManager(EnemyManager*);

// ENEMY
Enemy* NewEnemy(size*, char*, int);
void UpdateEnemy(SDL_Renderer*, Enemy*, double);
void RespawnEnemy(Enemy*);
void ShootEnemy(Enemy*, double);
void ShootEnemyBullets(Enemy* e);
void AI(Enemy*, double);
void DestroyEnemy(Enemy*);



#endif