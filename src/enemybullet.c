#include "enemybullet.h"

void InitEnemyBullet(EnemyBullet* enemyBullet, point point, size size, int dmg, float speed, char* path){
    //NewBullet(&enemyBullet->bullet, point, size, dmg, speed, path);
}

void RenderingEnemyBullet(SDL_Renderer* renderer, EnemyBullet* enemyBullet){
    RenderingBullet(renderer, &enemyBullet->bullet);
}