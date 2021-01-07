#include "bullet.h"
#include "list.h"

Bullet NewBullet(BulletType bulletType){
    Bullet bullet;
    if(bulletType == playerBullet){
        bullet.isActive = false;
        bullet.dmg = 50;
        bullet.speed = 50;
        bullet.go.position = NewPoint(10, 10);
        bullet.go.t_path = "assets/player/bullet.png";
        bullet.go.t_size = NewSize(20, 20);
    }
    return bullet;
}

void RenderingBullet(SDL_Renderer* renderer, Bullet* b){
    if(b->go.position.y < 0 - b->go.t_size.Height){
        b->isActive = false;
    }
    else{
        RendererGameobject(renderer, &b->go);
    }
}

void RenderingBullets(SDL_Renderer* renderer, List* bulletList, float deltaTime){
    int count = 0;
    Node* each = bulletList->__head;
    Bullet* freeBullet;
    while (each)
    {
        Node* next = each->next;
        if(((Bullet*)each->data)->isActive){
            freeBullet = (Bullet*)each->data;
            freeBullet->go.position.y += -1 * freeBullet->speed * deltaTime;
            RenderingBullet(renderer, freeBullet);
        }
        count++;
        each = next;
    }
    
}