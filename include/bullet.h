#ifndef BULLET_H
#define BULLET_H
#include "common.h"
#include "gameobj.h"
#include "renderer.h"
#include "list.h"

enum bulletType { playerBullet, enemyBullet };
typedef enum bulletType BulletType; 

typedef struct {
    GameObject go;
    int dmg;
    float speed;
    boolean isActive;
} Bullet;

Bullet NewBullet(BulletType bullet);
void RenderingBullet(SDL_Renderer* renderer, Bullet* b);
void RenderingBullets(SDL_Renderer* renderer, List* bulletList, float deltaTime);

#endif //BULLET_H