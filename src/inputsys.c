#include "inputsys.h"



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

void InitInputSystem(Input* input, char* buttons_char){
    input->isActive = true;
    InitButton(input, buttons_char);
}


void MoveInput(SDL_Renderer* renderer, SDL_Event* event, Input* inputSys, Character* c, size* size, double* deltatime, List* bullets){
    if(inputSys->isActive){

        if(event->type == SDL_KEYDOWN){

            if(event->key.keysym.scancode == inputSys->up){ //up
                if(c->go.position.y > 0)
                    c->go.position.y += -1 * c ->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->left){ //left
                if(c->go.position.x > 0)
                    c->go.position.x += -1 * c ->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->down){ //down
                if(c->go.position.y < (size->Height - 75) - c->go.t_size.Height)
                    c->go.position.y += 1 * c ->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->right){ //right
                if(c->go.position.x < (size->Width) - c->go.t_size.Width)
                    c->go.position.x += 1 * c ->speed * (*deltatime);
            }
            if(event->key.keysym.scancode == inputSys->shoot){

                Shoot(renderer, c, size, deltatime, bullets);
            }
        }

    }
}


void Shoot(SDL_Renderer* renderer, Character* c, size* size, double* deltaTime, List* bullletList){
    if(c->go.position.y > 0){
        int count = 0;
        int index = 0;
        Node* each = bullletList->__head;
        while(each){
            Node* next = each->next;
            if (!((Bullet*)each->data)->isActive){
                ((Bullet*)each->data)->isActive = true;
                ((Bullet*)each->data)->go.position.x = c->go.position.x +(c->go.t_size.Width * 0.5f) - 10;
                ((Bullet*)each->data)->go.position.y = c->go.position.y;
                index = count;
                break;
            }
            count++;
            each = next;
        }
    }
}
