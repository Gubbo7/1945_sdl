#include "inputsys.h"
#include "bullet.h"
#include "player.h"


void InitButton(Input* input, char* movement){
    if(!strcmp(movement, "WASD")){
        input->up = SDL_SCANCODE_W;
        input->left = SDL_SCANCODE_A;
        input->down = SDL_SCANCODE_S;
        input->right = SDL_SCANCODE_D;
        
    }
    else if(!strcmp(movement, "ARWS")){
        input->up = SDL_SCANCODE_UP;
        input->left = SDL_SCANCODE_LEFT;
        input->down = SDL_SCANCODE_DOWN;
        input->right = SDL_SCANCODE_RIGHT;
    }
    input->shoot = SDL_SCANCODE_SPACE;
}

Input* InitInputSystem(char* buttons_char){
    Input* input = (Input*)calloc(1, sizeof(Input));
    input->isActive = true;
    InitButton(input, buttons_char);
    return input;
}


void MoveInput(SDL_Event* event, Input* inputSys, Player* player, double* deltatime, List* bullets){
    if(inputSys->isActive){

        if(event->type == SDL_KEYDOWN){

            if(event->key.keysym.scancode == inputSys->up){ //up
                if(player->character->go->position->y > 0)
                    player->character->go->position->y += -1 * player->character ->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->left){ //left
                if(player->character->go->position->x > 0)
                    player->character->go->position->x += -1 * player->character->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->down){ //down
                if(player->character->go->position->y < (HEIGHT_WINDOW - 75) - player->character->go->t_size->Height)
                    player->character->go->position->y += 1 * player->character->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->right){ //right
                if(player->character->go->position->x < (WIDTH_WINDOW) - player->character->go->t_size->Width)
                    player->character->go->position->x += 1 * player->character->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->shoot){
                Shoot(player->character, deltatime, bullets);
                //PlayerDied(player, deltatime, 3);
                //player->isAlive = false;
            }
        }

    }
}


void Shoot(Character* c, double* deltaTime, List* bullletList){
    
    if(c->go->position->y > 0){
        int count = 0;
        int index = 0;
        Node* each = bullletList->__head;
        Bullet* tempBullet;
        while(each){
            Node* next = each->next;
            if (!((Bullet*)each->data)->go->isActive){
                tempBullet = ((Bullet*)each->data);
                tempBullet->go->isActive = true;
                tempBullet->go->position->x = c->go->position->x + (c->go->t_size->Width * 0.5f) - (tempBullet->go->t_size->Width * 0.5f);
                tempBullet->go->position->y = c->go->position->y + tempBullet->go->t_size->Height;
                index = count;
                break;
            }
            count++;
            each = next;
        }
    }
}

void DestroyInput(Input* input){
    free(input);
}