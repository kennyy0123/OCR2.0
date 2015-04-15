#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846
#include <SDL/SDL.h>
#include "rotation.h"

void rotation(float r)
{
	
	SDL_Surface* origin = NULL, *ecran = NULL, *dest = NULL;
	SDL_Rect destpos;

	destpos.x = 0;
	destpos.y = 0;

	if(SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur initialisation : %s\n", 
		SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
	ecran = SDL_SetVideoMode(650, 433, 32, SDL_HWSURFACE | SDL_RESIZABLE);
	origin = SDL_LoadBMP("sortie.bmp");
	dest = SDL_CentralRotation(origin, r);
	SDL_SaveBMP(dest, "sortie.bmp");

	SDL_BlitSurface(dest, NULL, ecran, &destpos);
	
	SDL_Flip(ecran);
	//pause();
	
	SDL_FreeSurface(origin);
	SDL_Quit();
}

SDL_Surface* SDL_CentralRotation(SDL_Surface* origin, float angle)
{
	SDL_Surface* destination;
	Uint32 couleur;
	int rcx, rcy; // position en x et y du centre de rotation
	int hx, wy; // hauteur et longueur de l'image
	float angle_radian;

	/* détermine la valeur en radian de l'angle*/
	angle_radian = -angle * M_PI / 180.0;

	/* 
	 * alloue la mémoire à l'espace de destination, attention, 
	 * la surface est de même taille
	 */
	destination = SDL_CreateRGBSurface(SDL_HWSURFACE, origin->w, origin->h,
	origin->format->BitsPerPixel,origin->format->Rmask, 
	origin->format->Gmask, origin->format->Bmask, origin->format->Amask);

	/*on vérifie que la mémoire a été allouée*/
	if(destination == NULL)
		return NULL;

	/* pour simplifier les notations*/
	rcx = origin->w/2;
	rcy = origin->h/2;

	for(int j = 0; j < origin->h; j++)
		for(int i = 0; i < origin->w; i++)
		{
		/* on détermine la valeur de pixel qui correspond 
		le mieux pour la position
		 * i,j de la surface de destination */

		/* on détermine la meilleure position sur la surface d'origine 
		en appliquant une matrice de rotation inverse*/
		hx = (int) (cos(angle_radian) * (i-rcx) + sin(angle_radian) 
		* (j-rcy)) + rcx;
		wy = (int) (-sin(angle_radian) * (i-rcx) + cos(angle_radian) 
		* (j-rcy)) + rcy;
		/* on vérifie que l'on ne sort pas des bords*/
		if (hx >= 0 && hx < origin->w && wy >= 0 && wy < origin->h)
		  {  
			couleur = getpixel(origin, hx, wy); //Lire pixel
			putpixel(destination, i, j, couleur); //Ecrire pixel
		  }
		}
	return destination;
}
