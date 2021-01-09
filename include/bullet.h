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

Bullet* NewBullet(BulletType bullet);
void RenderingBullet(SDL_Renderer* renderer, Bullet* b);
void RenderingBullets(SDL_Renderer* renderer, List* bulletList, float deltaTime);

void BulletDestroy(Bullet* b);

#endif //BULLET_H