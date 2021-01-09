#ifndef COMMON_H
#define COMMON_H
#define WIDTH_WINDOW 640 
#define HEIGHT_WINDOW 480

#include "SDL.h"
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "list.h"


enum boolean_enum { false, true };
typedef unsigned char boolean;

typedef unsigned int uint;


typedef struct {
    float Width;
    float Height;

} size;

typedef struct {
    float x;
    float y;
} point;

size* NewSize(float width, float height);
point* NewPoint(float x, float y);
point* RandomPoint(size* s);
void SizeDestroy(size* s);
void PointDestroy(point* p);
int GetRandomInRange(int lower, int upper);

#endif //COMMON_H
