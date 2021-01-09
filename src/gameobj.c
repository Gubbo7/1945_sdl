#include "gameobj.h"
#include "bullet.h"

GameObject* NewGameObj(point* p, size* size, char* t_path){
    GameObject* go = (GameObject*)calloc(1, sizeof(GameObject));
    go->position = p;
    go->t_path = t_path;
    go->t_size = size;
    go->isActive = true;
    return go;
}

void RenderGameobject(SDL_Renderer* r, GameObject* go){
    SDL_Texture* texture = NewTexture(r, go->t_path);
    RenderingTexture(r, texture, go->position, go->t_size);
    SDL_DestroyTexture(texture);
}

void AddGoToList(List* list, int n, char* elem, int type){
    if (!strcmp("bullet", elem))
    {
        for (int i = 0; i < n; i++)
        {
            AddToList(list, NewBullet((BulletType)type));
        }   
    }
    else if (!strcmp("island", elem)){
        for (int i = 0; i < n; i++)
        {
            AddToList(list, NewIsland((IslandsType)type));
        }
    }
    else if (!strcmp("background", elem)){
        for (int i = 0; i < n; i++)
        {
            AddToList(list, NewGameObj(NewPoint(0, 540 - HEIGHT_WINDOW * i), NewSize(WIDTH_WINDOW, HEIGHT_WINDOW), "assets/map/water2.png"));
        }
    }
}



GameObject* NewIsland(IslandsType it)
{
    GameObject* go;
    if(it == Normal)
    {
        size* size = NewSize(25, 45);
        go = NewGameObj(RandomPoint(size), size, "./assets/map/island1.png");
    }
    else if(it == Vulcan)
    {
        size* size = NewSize(40, 40);
        go = NewGameObj(RandomPoint(size), size, "./assets/map/island2.png");
    }
    else if(it == Sand)
    {
        size* size = NewSize(40, 40);
        go = NewGameObj(RandomPoint(size), size, "./assets/map/island3.png");
    }
    go->isActive = true;
    return go;
}

void RenderGOList(SDL_Renderer* renderer, List* goList, boolean bg, float deltaTime)
{
    int speed = 25;
    int count = 0;
    Node* each = goList->__head;
    GameObject* free_GO;
    while (each)
    {
        Node* next = each->next;
        if(((GameObject*)each->data)->isActive){
            free_GO = (GameObject*)each->data;
            free_GO->position->y += 1 * speed * deltaTime;
            RenderGOActive(renderer, free_GO, bg);
        }
        count++;
        each = next;
    }
}

void RenderGOActive(SDL_Renderer* renderer, GameObject* go, boolean bg)
{
    if(!bg && go->position->y > (HEIGHT_WINDOW - 75) + go->t_size->Height){ //380 ref win height - UI
        go->position = RandomPoint(go->t_size);
    }
    else if(bg && go->position->y > -10){
        go->position->y = HEIGHT_WINDOW - go->t_size->Height - 75;
    }
    else{
        RenderGameobject(renderer, go);
    }
}

void DestroyGameObj(GameObject* go){
    if(go)
        free(go);
}