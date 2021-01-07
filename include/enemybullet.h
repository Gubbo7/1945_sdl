#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"

typedef struct {
    Bullet bullet;
} EnemyBullet;

void InitEnemyBullet(EnemyBullet* enemyBullet, point point, size size, int dmg, float speed, char* path);
void RenderingEnemyBullet(SDL_Renderer* renderer, EnemyBullet* enemyBullet);



#endif //ENEMYBULLET_H