#include "playerbullet.h"

void InitPlayerBullet(SDL_Renderer* renderer, PlayerBullet* playerBullet, point point, size size, int dmg, float speed){
    //NewBullet(&playerBullet->bullet, point, size, dmg, speed, "assets/player/bullet.png");
    
}

void RenderingPlayerBullet(SDL_Renderer* renderer, PlayerBullet* playerBullet){
    RenderingBullet(renderer, &playerBullet->bullet);
}
    
