#include "physics.h"

PhysicsManager* NewPhysicsManager(Player* playerSign, EnemyManager* enemymgr){
    PhysicsManager* physicsMgr = (PhysicsManager*)calloc(1, sizeof(PhysicsManager));
    physicsMgr->player = playerSign;
    physicsMgr->enemymgr = enemymgr;
    return physicsMgr;
}

void DestroyPhysicsManager(PhysicsManager* physicsMgr){
    free(physicsMgr);
}

void CheckCollision(PhysicsManager* physicsMgr){
    CheckCollisionPlayerEnemy(physicsMgr);
    CheckCollisionPlayerBullets(physicsMgr);
    CheckCollisionEnemyBullets(physicsMgr);
}

void CheckCollisionPlayerEnemy(PhysicsManager* physicsMgr){
    Player* player = physicsMgr->player;
    Node* each = physicsMgr->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (player->isAlive && enemy->isAlive)
        {
            if(CheckCollisionPoint(player->character->go, enemy->character->go)){
                //printf("collisione player_to_enemy\n");
                int player_hp = player->character->hp;
                player->character->hp -= enemy->character->hp;
                enemy->character->hp -= player_hp;
                player->score += enemy->score;
                break;
            }
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
    player = NULL;
}

void CheckCollisionEnemyBullets(PhysicsManager* physicsMgr){
    Node* each = physicsMgr->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (enemy->isAlive && !enemy->isDead && enemy->character->go->position->y > 0)
        {
            CheckCollisionEnemyBulletsPlayer(physicsMgr->player, enemy);
            //CheckCollisionPlayerBulletEnemy(pm, bullet);
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
}

void CheckCollisionEnemyBulletsPlayer(Player* player, Enemy* enemy){
    Node* each = enemy->character->bullets->__head;
    Bullet* bullet;
    while (each)
    {
        Node* next = each->next;
        bullet = (Bullet*)each->data;
        if (bullet->go->isActive)
        {
            if(CheckCollisionPoint(player->character->go, bullet->go)){
                //printf("collision enemybullet_player\n");
                bullet->go->isActive = false;
                player->character->hp -= bullet->dmg;
                break;
            }
        }
        each = next;
    }
    bullet = NULL;
    each = NULL;
}


void CheckCollisionPlayerBullets(PhysicsManager* physicsMgr){
    Node* each = physicsMgr->player->character->bullets->__head;
    Bullet* bullet;
    while (each)
    {
        Node* next = each->next;
        bullet = (Bullet*)each->data;
        if (bullet->go->isActive == true)
        {
            CheckCollisionPlayerBulletEnemy(physicsMgr, bullet);
        }
        each = next;
    }
    bullet = NULL;
    each = NULL;
}

void CheckCollisionPlayerBulletEnemy(PhysicsManager* physicsMgr, Bullet* bullet){
    Node* each = physicsMgr->enemymgr->enemys->__head;
    Enemy* enemy;
    while (each)
    {
        Node* next = each->next;
        enemy = (Enemy*)each->data;
        if (enemy->isAlive && !enemy->isDead && enemy->character->go->position->y > 0)
        {
            if(CheckCollisionPoint(enemy->character->go, bullet->go)){
                //printf("collision playerbullet -> enemy\n");
                bullet->go->isActive = false;
                enemy->character->hp -= bullet->dmg;
                if (enemy->character->hp <= 0)
                {
                    physicsMgr->player->score += enemy->score;
                }
                break;
            }
        }
        each = next;
    }
    enemy = NULL;
    each = NULL;
}

boolean CheckCollisionPoint(GameObject* player, GameObject* enemy){
    point* enemy_min = enemy->position;
    point* enemy_max = GetMaxPointGameObject(enemy);
    // printf("\n\n--------------\nenemy_min x: %f y: %f \n", enemy_min->x, enemy_min->y);
    // printf("enemy_max x: %f y: %f \n--------------\n\n", enemy_max->x, enemy_max->y);
    if (PointInRect(enemy_min, player) || PointInRect(enemy_max, player) || PointInRect(NewPoint(enemy_max->x, enemy_min->y), player) || PointInRect(NewPoint(enemy_min->x, enemy_max->y), player))
    {
        enemy_max = NULL;
        enemy_min = NULL;
        return true;
    }
    else {
        enemy_max = NULL;
        enemy_min = NULL;
        return false;
    }
}

boolean PointInRect(point* p, GameObject* go){
    point* min = go->position;
    point* max = GetMaxPointGameObject(go);
    // printf("bullet_min x: %f y: %f \n", min->x, min->y);
    // printf("bullet_max x: %f y: %f \n", max->x, max->y);
    if (p->x >= min->x && p->y >= min->y)
    {
        if (p->x <= max->x && p->y <= max->y)
        {
            max = NULL;
            min = NULL;
            return true;
        }
        else{
            max = NULL;
            min = NULL;
            return false;
        }
    }
    else{
        max = NULL;
        min = NULL;
        return false;
    }
}

point* GetMaxPointGameObject(GameObject* go){
    return NewPoint(go->position->x + go->t_size->Width, go->position->y + go->t_size->Height);
}