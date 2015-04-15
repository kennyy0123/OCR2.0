#include "detection.h"
void mypause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

int main()
    {
    initDetect();
    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;
    positionFond.x = 0;
    positionFond.y = 0;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(SDL_LoadBMP("sdl_icone.bmp"), NULL);
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("TRY", NULL);
    imageDeFond = SDL_LoadBMP("test.bmp");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_Flip(ecran);
    mypause();
    SDL_FreeSurface(imageDeFond);
    SDL_Quit();
    return EXIT_SUCCESS;
    }
