#include "common.h"

size NewSize(float width, float height){
    size win;
    win.Width = width;
    win.Height = height;
    return win;
}

point NewPoint(float x, float y){
    point point;
    point.x = x;
    point.y = y;
    return point;
}