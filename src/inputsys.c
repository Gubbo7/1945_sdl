#include "inputsys.h"
#include "bullet.h"
#include "character.h"


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
    input->explosion = Mix_LoadWAV("./assets/audio/snd_explosion1.wav");
    Mix_VolumeChunk(input->explosion, SDL_MIX_MAXVOLUME / 8);
    InitButton(input, buttons_char);
    return input;
}

boolean UpdateInputSystem(SDL_Event* event, Input* input, Character* c, double deltaTime){
    while (SDL_PollEvent(event)){
        if (event->type == SDL_QUIT) {
                free(event);
                return true;
            }
        MoveInput(event, input, c, deltaTime);
    }
    return false;
}

void MoveInput(SDL_Event* event, Input* inputSys, Character* character, double deltaTime){
    if(inputSys->isActive){

        if(event->type == SDL_KEYDOWN){

            if(event->key.keysym.scancode == inputSys->up){ //up
                if(character->go->position->y > 0)
                    character->go->position->y += -1 * character ->speed * (deltaTime);
                else
                    character->go->position->y = 0;
            }
            if(event->key.keysym.scancode == inputSys->left){ //left
                if(character->go->position->x > 0)
                    character->go->position->x += -1 * character->speed * (deltaTime);
                else
                    character->go->position->x = 0;
            }
            if(event->key.keysym.scancode == inputSys->down){ //down
                if(character->go->position->y < (HEIGHT_WINDOW - 75) - character->go->t_size->Height)
                    character->go->position->y += 1 * character->speed * (deltaTime);
                else
                    character->go->position->y = (HEIGHT_WINDOW - 75) - character->go->t_size->Height;
            }
            if(event->key.keysym.scancode == inputSys->right){ //right
                if(character->go->position->x < (WIDTH_WINDOW) - character->go->t_size->Width)
                    character->go->position->x += 1 * character->speed * (deltaTime);
                else
                    character->go->position->x = (WIDTH_WINDOW) - character->go->t_size->Width;
            }
            if(event->key.keysym.scancode == inputSys->shoot){
                Shoot(character);
                Mix_PlayChannel(-1, inputSys->explosion, 0);
            }
        }

    }
}


void Shoot(Character* c){
    
    if(c->go->position->y > 0){
        int count = 0;
        int index = 0;
        Node* each = c->bullets->__head;
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
        each = NULL;
        tempBullet = NULL;
    }
}

void DestroyInput(Input* input){
    free(input);
}