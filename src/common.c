#include "common.h"

size* NewSize(float width, float height){
    size* win = (size*)calloc(1, sizeof(size));
    win->Width = width;
    win->Height = height;
    return win;
}

point* NewPoint(float x, float y){
    point* p = (point*)calloc(1, sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

void SizeDestroy(size* s){
    free(s);
}

void PointDestroy(point* p){
    free(p);
}

int GetRandomInRange(int lower, int upper)
{
    return (rand() %(upper - lower + 1)) + lower;
}

point* RandomPoint(size* s)
{
    int posX = GetRandomInRange(0, 480 - 1);
    int posY = -GetRandomInRange(s->Height, s->Height - 300);
    printf("random x: %d y: %d \n ", posX, posY);

    return NewPoint(posX, posY);
}