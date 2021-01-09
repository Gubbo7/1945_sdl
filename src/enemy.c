#include "enemy.h"

Enemy* NewEnemy(point* p, size* s, int hp, float speed, char* path){
    Enemy* enemy = (Enemy*)calloc(1, sizeof(Enemy*));
    enemy->character = NewCharacter(p, s, hp, speed, path);
    return enemy;
}

void RenderEnemy(SDL_Renderer* renderer, Enemy* enemy){
    RenderCharacter(renderer, enemy->character);
}

void EnemyDie(Enemy* enemy){
    if(enemy->character->hp <= 0){
        DestroyEnemy(enemy);
    }
}

void DestroyEnemy(Enemy* enemy){
    DestroyCharacter(enemy->character);
    free(enemy);
}