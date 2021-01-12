#include "ui.h"

Interface* NewInterface(){
    Interface* i = (Interface*)calloc(1,sizeof(Interface));
    i->UIList = NewList();
    return i;
}

void AddUIList(Interface* i, point* p, size* s, char* texture_path){
    AddToList(i->UIList, NewUI(p,s,texture_path));
}

UI* NewUI(point* p, size* s, char* texture_path){
    UI* ui = (UI*)calloc(1,sizeof(UI));
    ui->path = texture_path;
    ui->position = p;
    ui->size = s;
    return ui;
}

void UpdateInterface(SDL_Renderer* renderer, Interface* i, double dt){
    Node* each = i->UIList->__head;
    while (each)
    {
        Node* next = each->next;
        RenderingUI(renderer, (UI*)each->data);
        each = next;
    }
}

void RenderingUI(SDL_Renderer* renderer, UI* ui){
    SDL_Texture* texture = NewTexture(renderer,ui->path);
    RenderingTexture(renderer,texture, ui->position,ui->size);
    SDL_DestroyTexture(texture);
}

void DestroyInterface(Interface* i){
    Node* each = i->UIList->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyUI((UI*)each->data);
        each = next;
    }
    free(each);
    DestroyList(i->UIList);
    free(i);
}

void DestroyUI(UI* ui){
    if(ui != NULL){
        PointDestroy(ui->position);
        SizeDestroy(ui->size);
        free(ui);
    }
}