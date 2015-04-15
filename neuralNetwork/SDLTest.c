#include <stdio.h>
#include <SDL.h>
#include <SDL/SDL_ttf.h>

#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32


void pause()
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
    SDL_Surface *ecran = NULL, *imageDeFond = NULL;
    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;
    TTF_Font *police = NULL;
    SDL_Color couleurNoire = {0, 0, 0,0};

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(800, 70, 32, SDL_HWSURFACE);
    if(TTF_Init() == -1)//Init de TTF
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
police = TTF_OpenFont("lettres/liberation.ttf", 60);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    /* Chargement d'une image Bitmap dans une surface */
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
    imageDeFond =TTF_RenderText_Blended(police, "abcdefghijklmnopqrstuvwxyz", couleurNoire);
    /* On blitte par-dessus l'écran */
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
    SDL_SaveBMP(ecran,"sortie.bmp");

    SDL_Flip(ecran);
    pause();

    TTF_CloseFont(police); /* Doit être avant TTF_Quit() */
    TTF_Quit();//free of TTF
    SDL_FreeSurface(imageDeFond); /* On libère la surface */
    SDL_Quit();

    return EXIT_SUCCESS;
}




