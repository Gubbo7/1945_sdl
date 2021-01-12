#include "player.h"

Player* NewPlayer(point* p, size* s, Input* input, int hp, float speed, char* text_path){// int hp, float speed, char* path, Point* p, Size* s){
    Player* player = (Player*)calloc(1, sizeof(Player));
    player->character = NewCharacter(p, s, hp, speed, text_path);
    player->lives = 3;
    player->isAlive = true;
    player->isDead = false;
    player->life1 = NewGameObj(NewPoint(100,HEIGHT_WINDOW-73), NewSize(40, 40), (char*)"./assets/ui/life.png");
    player->life2 = NewGameObj(NewPoint(55,HEIGHT_WINDOW-73), NewSize(40, 40), (char*)"./assets/ui/life.png");
    player->life3 = NewGameObj(NewPoint(10,HEIGHT_WINDOW-73), NewSize(40, 40), (char*)"./assets/ui/life.png");
    player->character->bullets = NewList();
    AddGoToList(player->character->bullets, 10, (char*)"bullet", playerBullet);
    player->input = input;
    return player;
}

boolean UpdatePlayer(SDL_Renderer* renderer, SDL_Event* events, Player* player, double dt){
    UpdateBullets(renderer, player->character->bullets, dt);

    switch(player->lives){
        case 3:
            RenderGameobject(renderer, player->life1);
            RenderGameobject(renderer, player->life2);
            RenderGameobject(renderer, player->life3);
            break;
        case 2:
            RenderGameobject(renderer, player->life1);
            RenderGameobject(renderer, player->life2);
            break;
        case 1:
            RenderGameobject(renderer, player->life1);
            break;
    }

    if(player->character->hp > 0){
        //player->character->hp -= 0.05f;
    }
    else if (player->character->hp <= 0 && player->lives > 0 && player->isAlive)
    {
        printf("hai perso una vita! :(\n");
        player->lives--;
        player->character->go->isActive = false;
        player->isAlive = false;
        player->input->isActive = false;
    }

    if (player->isAlive == false && player->lives != 0)
    {
         Mix_PlayChannel(-1, player->explosion, 0);
        if(RenderingThisAnimation(renderer, player->character->animator, "explosion", player->character->go->position, dt)){
            player->character->hp = 100;
            player->character->go->isActive = true;
            player->isAlive = true;
            player->input->isActive = true;
            player->character->go->position = NewPoint(290,180);
        }
    }
    else if (player->isAlive == false && player->lives == 0 && !player->isDead){
        Mix_PlayChannel(-1, player->explosion, 0);
        if(RenderingThisAnimation(renderer, player->character->animator, "explosion", player->character->go->position, dt)){
            player->character->go->isActive = false;
            player->isDead = true;
            player->input->isActive = false;
        }
    }
    
    RenderInt(renderer, player->font, player->score, NewRect(NewPoint(200, HEIGHT_WINDOW-42), NewSize(20,20)));

    UpdateCharacter(renderer, player->character, dt);

    // draw player HP
    // SDL_Texture* texture = NewTexture(renderer,(char*)"./assets/ui/hp.png");
    // RenderingTexture(renderer,texture, NewPoint(12, HEIGHT_WINDOW - 30), NewSize(126 * player->character->hp / 100, 9));
    // SDL_DestroyTexture(texture);

    //SDL_RenderDrawRect(renderer, NewRect(NewPoint(12, HEIGHT_WINDOW -39), NewSize(126 * player->Character_->Hp / 100, 10)));
    RenderingPath(renderer, (char*)"./assets/ui/hp.png", NewPoint(12, HEIGHT_WINDOW -40), NewSize(126 * player->character->hp / 100, 13));

    int done = UpdateInputSystem(events, player->input, player->character, dt);

    if (!done && !player->isAlive && player->isDead)
    {
        printf("game over!\n");
        SDL_Delay(1000);
        done = true;
    }
    return done;
}

void DestroyPlayer(Player* p){
    DestroyCharacter(p->character);
    DestroyGameObj(p->life1);
    DestroyGameObj(p->life2);
    DestroyGameObj(p->life3);
    DestroyInput(p->input);
    DestroyFont(p->font);
    Mix_FreeChunk(p->explosion);
    free(p);
}
