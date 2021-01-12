#include "enemy.h"

Enemy* NewEnemy(size* s, char* texture, int score){
    Enemy* enemy = (Enemy*)calloc(1, sizeof(Enemy));
    enemy->character = NewCharacter(NewPoint(0,0), s, 50, 30, texture);
    enemy->score = score;
    //enemy->DelayShoot = 1;
    enemy->timeShoot = 1;
    enemy->isAlive = true;
    enemy->isDead = false;
    enemy->shoot = Mix_LoadWAV("./assets/audio/snd_explosion1.wav");
    Mix_VolumeChunk(enemy->shoot, SDL_MIX_MAXVOLUME / 14);
    enemy->explosion = Mix_LoadWAV("./assets/audio/snd_explosion2.wav");
    Mix_VolumeChunk(enemy->explosion, SDL_MIX_MAXVOLUME / 15);
    AddGoToList(enemy->character->bullets, 10, (char*)"bullet", enemyBullet);
    AddAnimation(enemy->character, "main", texture, NewRect(enemy->character->go->position, NewSize(32,32)), 3, 0.05f);
    AddAnimation(enemy->character, "explosion", "./assets/enemy/explosion1_strip6.png", NewRect(enemy->character->go->position, NewSize(32,32)), 6, 0.1f);
    enemy->character->go->position->x = GetRandomInRange(100, WIDTH_WINDOW - (100 + s->Width));
    enemy->character->go->position->y = -GetRandomInRange(s->Height, s->Height - 300);
    return enemy;    
}

void UpdateEnemy(SDL_Renderer* renderer, Enemy* enemy, double deltaTime){

    UpdateBullets(renderer, enemy->character->bullets, deltaTime);
    ShootEnemy(enemy, deltaTime);

    if(enemy->character->hp > 0 && enemy->character->go->position->y > 0){
        //enemy->Character_->Hp -= 0.03f;
    }
    else if (enemy->character->hp <= 0 && !enemy->isDead)
    {
        enemy->isAlive = false;
        enemy->character->go->isActive = false;
        Mix_PlayChannel(-1, enemy->explosion, 0);
        if(RenderingThisAnimation(renderer, enemy->character->animator, "explosion", enemy->character->go->position, deltaTime)){
            enemy->isDead = true;
        }
    }

    RespawnEnemy(enemy);

    UpdateCharacter(renderer, enemy->character, deltaTime);
}

void ShootEnemy(Enemy* enemy, double deltaTime){
    enemy->timeShoot -= deltaTime;
    if (enemy->timeShoot <= 0)
    {
        ShootEnemyBullets(enemy);
        enemy->timeShoot = GetRandomInRange(2,7);
    }
}

void ShootEnemyBullets(Enemy* enemy){
    if (enemy->character->go->position->y > 0)
    {
        int count = 0;
        int index = 0;
        Node* each = enemy->character->bullets->__head;
        Bullet* tempBullet;
        while (each)
        {
            Node* next = each->next;
            if (((Bullet*)each->data)->go->isActive == false)
            {
                tempBullet = ((Bullet*)each->data); 
                tempBullet->go->isActive = true;
                Mix_PlayChannel(-1, enemy->shoot, 0);
                tempBullet->go->position->x = enemy->character->go->position->x + (enemy->character->go->t_size->Width * 0.5f) - (tempBullet->go->t_size->Width * 0.5f);
                tempBullet->go->position->y = enemy->character->go->position->y + tempBullet->go->t_size->Height;
                index = count;
                //printf("count: %d\nactive: %d\n", index, (int)((Bullet*)each->data)->Go->IsActive);
                break;
            }
            count++;
            each = next;
        }
        each = NULL;
        tempBullet = NULL;
    }
}

void RespawnEnemy(Enemy* enemy){
    if(enemy->character->go->position->y >= HEIGHT_WINDOW - 90 || enemy->isDead){
        enemy->character->go->position->x = GetRandomInRange(100, WIDTH_WINDOW - (100 + enemy->character->go->t_size->Width));
        enemy->character->go->position->y = -GetRandomInRange(enemy->character->go->t_size->Height, enemy->character->go->t_size->Height - 300);
        enemy->isAlive = true;
        enemy->isDead = false;
        enemy->character->go->isActive = true;
        enemy->character->hp = 50;
        //printf("enemy rispawnato!\n");
    }
}

void DestroyEnemy(Enemy* enemy){
    DestroyCharacter(enemy->character);
    Mix_FreeChunk(enemy->explosion);
    Mix_FreeChunk(enemy->shoot);
    free(enemy);
}

EnemyManager* NewEnemyManager(){
    EnemyManager* enemymgr = (EnemyManager*)calloc(1, sizeof(EnemyManager));
    enemymgr->enemys = NewList();
    return enemymgr;    
}

void DestroyEnemyManager(EnemyManager* enemymgr){
    Node* each = enemymgr->enemys->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyEnemy(((Enemy*)each->data));
        each = next;
    }
    each = NULL;
    DestroyList(enemymgr->enemys);
    free(enemymgr);
}

void AddEnemyManagerList(EnemyManager* enemymgr, size* s, char* path, int score){
    AddToList(enemymgr->enemys, NewEnemy(s, path, score));
}

void UpdateEnemyManager(SDL_Renderer* renderer, EnemyManager* enemymgr, double deltaTime){
    Node* each = enemymgr->enemys->__head;
    while (each)
    {
        Node* next = each->next;
        AI(((Enemy*)each->data), deltaTime);
        UpdateEnemy(renderer, ((Enemy*)each->data), deltaTime);
        each = next;
    }
    each = NULL;
}

void AI(Enemy* enemy, double deltaTime){
    enemy->character->go->position->y += enemy->character->speed * deltaTime;
}