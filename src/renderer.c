#include "renderer.h"

int RenderingTexture(SDL_Renderer* r, SDL_Texture* tex, point* p, size* s){
    SDL_Rect* rect = NewRect(p,s);
    int res =  SDL_RenderCopy(r, tex, NULL, rect);
    DestroyRect(rect);
    return res;
}

SDL_Texture* NewTexture(SDL_Renderer* renderer, char* path_file){
    return (SDL_Texture*)IMG_LoadTexture(renderer, path_file); 
}

SDL_Rect* NewRect(point* p, size* s){
    SDL_Rect* rect_ = (SDL_Rect*)calloc(1, sizeof(SDL_Rect));
    rect_->x = p->x;
    rect_->y = p->y; 
    rect_->w = s->Width; 
    rect_->h = s->Height;
    return rect_;
}

void DestroyRect(SDL_Rect* rect){
    free(rect);
}

// animation
Animator* NewAnimator(){
    Animator* animator = (Animator*)calloc(1,(sizeof(Animator)));
    animator->animations = NewList();
    return animator;
}

void DestroyAnimator(Animator* animator){
    DestroyListAnimation(animator->animations);
    free(animator);
}

Animation* NewAnimation(char* name_animation, char* texture_path, SDL_Rect* src, int nFrames, double TimeFrame){
    Animation* animation = (Animation*)calloc(1,(sizeof(Animation)));

    animation->name = name_animation;
    animation->currFrame = 0;
    animation->totFrames = nFrames;
    animation->delayFrame = TimeFrame;
    animation->timeFrame = TimeFrame;
    animation->texture_path = texture_path;
    animation->frameSize = NewSize(src->w , src->h);
    animation->list = NewList();
    for (int i = 0; i < animation->totFrames; i++){
        AddToList(animation->list, NewRect(NewPoint(src->w * i,src->y), animation->frameSize));
    };
    return animation;
}

void DestroyListAnimation(List* animations){
    Node* each = animations->__head;
    while (each)
    {
        Node* next = each->next;
        DestroyAnimation(((Animation*)each->data));
        each = next;
    }
}

void DestroyAnimation(Animation* anim){
    SizeDestroy(anim->frameSize);
    DestroyList(anim->list);
    free(anim);
}

boolean RenderingThisAnimation(SDL_Renderer* r, Animator* anim, char* animation_name, point* p, double deltatime){
    int count = 0;
    boolean finished = false;
    Node* each = anim->animations->__head;
    Animation* anim_app;
    while (each)
    {
        Node* next = each->next;
        if(!strcmp(((Animation*)each->data)->name, animation_name)){
            //printf("\nanimation_name: %s\n", animation_name);
            anim_app = ((Animation*)each->data);
            finished = RenderingListAnimation(r, anim_app, NewRect(p,anim_app->frameSize), deltatime);
            break;
        }
        count++;
        each = next;
    }
    return finished;
}

int RenderingPath(SDL_Renderer* renderer, char* path, point* p, size* s){
    SDL_Texture* t = NewTexture(renderer, path);
    int res = RenderingTexture(renderer, t, p, s);
    SDL_DestroyTexture(t);
    return res;
}

boolean RenderingListAnimation(SDL_Renderer* r, Animation* anim, SDL_Rect* dst, double deltatime){
    int count = 0;
    Node* each = anim->list->__head;
    boolean first = true;
    boolean finished = false;
    SDL_Rect* last;
    while (each)
    {
        Node* next = each->next;
        if(count == anim->currFrame){
            //printf("animation_frame: %d\n", anim->currFrame);
            if (anim->timeFrame > 0)
            {
                anim->timeFrame -= deltatime;
                //printf("\ndeltatime: %f \nframe: %d \ndelay_frame: %f\n", deltatime, anim->currFrame, anim->TimeFrame);
            }
            else{
                last = (SDL_Rect*)each->data;
                if (anim->currFrame == (anim->totFrames - 1))
                {
                    finished = true;
                }
                anim->currFrame = (anim->currFrame < (anim->totFrames - 1)) ? anim->currFrame + 1 : 0;
                anim->timeFrame = anim->delayFrame;
                //printf("\nsrc changed\ncurr_frame: %d \ndelay restart %f\n", anim->currFrame, anim->TimeFrame);
            }
            if (first)
            {
                last = (SDL_Rect*)each->data;
                RenderingAnimation(r,anim->texture_path,last,dst);
                first = false;
            }
            else{
                RenderingAnimation(r,anim->texture_path,last,dst);
            }
        }
        count++;
        each = next;
    }
    return finished;
}

void RenderingAnimation(SDL_Renderer* r, char* t_p, SDL_Rect* src, SDL_Rect* dst){
    //printf("SRC x: %d y: %d  \t w: %d h:%d\n",src->x,src->y,src->w,src->h);
    // printf("DST x: %d y: %d  \t w: %d h:%d\n",dst->x,dst->y,dst->w,dst->h);
    // printf("path: %s\n", t_p);
    SDL_Texture* t = NewTexture(r,t_p);
    if (t == NULL)
    {
        printf("non ce n'e' texture\n");
    }
    //NewRect(NewPoint(10,10), NewSize(65,65))
    SDL_RenderCopy(r,t,src,dst);
    SDL_DestroyTexture(t);
}

// windows
void CloseWindow(SDL_Renderer* r, SDL_Window* win){
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(win);
    SDL_Quit();
}