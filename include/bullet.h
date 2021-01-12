#ifndef BULLET_H
#define BULLET_H

#include "common.h"
#include "gameobj.h"
#include "renderer.h"

typedef struct {
    GameObject* go;
    int dmg;
    float speed;
} Bullet;

enum bulletType { playerBullet, enemyBullet };
typedef enum bulletType BulletType; 

Bullet* NewBullet(BulletType);
void RenderingBullet(SDL_Renderer*, Bullet* );
void RenderingBullets(SDL_Renderer*, List*, double);

void BulletDestroy(Bullet*);

#endif //BULLET_H