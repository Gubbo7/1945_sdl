#include "bullet.h"
#include "list.h"

Bullet* NewBullet(BulletType bulletType){
    Bullet* bullet = (Bullet*)calloc(1, sizeof(Bullet));

    if(bulletType == playerBullet){
        bullet->dmg = 30;
        bullet->speed = 100;
        bullet->go = NewGameObj(NewPoint(20, 20), NewSize(15, 15), "./assets/player/bullet.png");
        bullet->go->isActive = false;
    }
    else if(bulletType == enemyBullet){
        bullet->dmg = 30;
        bullet->speed = 100;
        bullet->go = NewGameObj(NewPoint(20, 20), NewSize(15, 15), "./assets/enemy/enemybullet1.png");
        bullet->go->isActive = false;
    }
    return bullet;
}

void RenderingBullet(SDL_Renderer* renderer, Bullet* b){
    if(b->go->position->y < 0 - b->go->t_size->Height){
        b->go->isActive = false;
    }
    else{
        RenderGameobject(renderer, b->go);
    }
}

void RenderingBullets(SDL_Renderer* renderer, List* bulletList, float deltaTime){
    int count = 0;
    Node* each = bulletList->__head;
    Bullet* freeBullet;
    while (each)
    {
        Node* next = each->next;
        if(((Bullet*)each->data)->go->isActive == true){
            freeBullet = (Bullet*)each->data;
            freeBullet->go->position->y += -1 * freeBullet->speed * deltaTime;
            RenderingBullet(renderer, freeBullet);
        }
        count++;
        each = next;
    }
    
}

void DestroyBullet(Bullet* b){
    DestroyGameObj(b->go);
    free(b);
}