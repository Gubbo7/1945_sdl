#include <map.h>


void RenderWater(SDL_Renderer* rend)
{
    SDL_Texture* water_texture = NewTexture(rend, "assets/map/water.png");
    
    for (int i = 0; i<=19; i++)
    {
        for (int j = 0; j <= 12; j++)
        {
            RenderingTexture(rend, water_texture, NewPoint(32 * i, 32 * j), NewSize(32, 32));           
        }          
    }
    SDL_DestroyTexture(water_texture);
}