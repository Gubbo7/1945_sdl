#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H

#include "bullet.h"

// enum perks { normal, fastShoot, doubleShoot};

typedef struct {
    Bullet bullet;
} PlayerBullet;

void InitPlayerBullet(SDL_Renderer* renderer, PlayerBullet* playerBullet, point point, size size, int dmg, float speed);

void RenderingPlayerBullet(SDL_Renderer* renderer, PlayerBullet* playerBullet);

#endif //PLAYERBULLET_H