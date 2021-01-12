#ifndef PHYSICS_H
#define PHYSICS_H

#include "common.h"
#include "player.h"
#include "enemy.h"

typedef struct
{
    Player* player;
    EnemyManager* enemymgr;
} PhysicsManager;

PhysicsManager* NewPhysicsManager(Player*, EnemyManager*);
void DestroyPhysicsManager(PhysicsManager*);

// PRIMARY
void CheckCollision(PhysicsManager* physicsMgr);
point* GetMaxPointGameObject(GameObject* go);
boolean CheckCollisionPoint(GameObject* go1, GameObject* go2);
boolean PointInRect(point* p, GameObject* go);

// ENEMY <=> PLAYER
void CheckCollisionPlayerEnemy(PhysicsManager* physicsMgr);

// PLAYER_BULLET -> ENEMY
void CheckCollisionPlayerBullets(PhysicsManager* physicsMgr);
void CheckCollisionPlayerBulletEnemy(PhysicsManager* physicsMgr, Bullet* bullet);

// ENEMY_BULLET -> PLAYER
void CheckCollisionEnemyBullets(PhysicsManager* physicsMgr);
void CheckCollisionEnemyBulletsPlayer(Player* player, Enemy* enemy);

#endif // PHYSICS_H