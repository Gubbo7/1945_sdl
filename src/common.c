#include "common.h"

size* NewSize(float width, float height){
    size* s = (size*)calloc(1, sizeof(size));
    s->Width = width;
    s->Height = height;
    return s;
}

point* NewPoint(float x, float y){
    point* p = (point*)calloc(1, sizeof(point));
    p->x = x;
    p->y = y;
    return p;
}

int GetRandomInRange(int lower, int upper)
{
    time_t seconds = time(NULL);
    return (rand() * seconds %(upper - lower + 1)) + lower;
}

point* RandomPoint(size* s)
{
    int posX = GetRandomInRange(0, WIDTH_WINDOW - s->Width - 1);
    int posY = -GetRandomInRange(s->Height, s->Height - 300);

    return NewPoint(posX, posY);
}

void SizeDestroy(size* s){
    free(s);
}

void PointDestroy(point* p){
    free(p);
}