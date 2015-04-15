#include <stdlib.h>
#include <stdio.h>
#include "filtre.h"
#include <math.h>

void mainbin(gchar *path)
{

SDL_Surface *ecran=NULL, *imagedefond=NULL, *empty=NULL;
SDL_Rect positionFond;

positionFond.x = 0;
positionFond.y = 0;

/* Initialisation des parametres SDL*/

SDL_Init(SDL_INIT_VIDEO); //Initialise la vidéo
imagedefond = SDL_LoadBMP(path);
empty = SDL_CreateRGBSurface(0, imagedefond->w, imagedefond->h,32, 0,
0,0, 0);
//ecran = SDL_SetVideoMode(imagedefond->w,imagedefond->h ,32, SDL_HWSURFACE);
// Permet de créer une fêtre.
//SDL_WM_SetCaption("Filtre Noir et blanc SDL",NULL); // Titre à La Fenetre
//SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));

/*On affiche l'image à l'écran*/
Gray_Scale(imagedefond);
Otsu(imagedefond, empty);
//Binarisation(imagedefond);
SDL_BlitSurface(imagedefond,NULL,ecran,&positionFond);
SDL_BlitSurface(empty,NULL,ecran,&positionFond);

//pause();

/* Libération de la mémoire */
//SDL_SaveBMP(imagedefond,"sortie.bmp");
SDL_SaveBMP(empty,"sortie.bmp");

SDL_FreeSurface(imagedefond);
SDL_FreeSurface(empty);
SDL_Quit();

}


/*void pause()
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
}*/

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
        break;

    case 4:
        return *(Uint32 *)p;
        break;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to set */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
}


void Gray_Scale(SDL_Surface* surface)
{
int x,y;
Uint8 r_s,g_s,b_s,a_s;
Uint32 pixel_s;
SDL_LockSurface(surface);

for (y=0; y < surface->h;y++)
 {
  for ( x=0;x < surface->w;x++)
   {
    pixel_s = getpixel(surface,x,y);
    SDL_GetRGBA(pixel_s,surface->format,&r_s,&g_s,&b_s,&a_s);
    Uint8 Moyenne = (Uint8)(0.30 * r_s + 0.59 * g_s + 0.11 * b_s);

                        r_s = Moyenne;
                        g_s = Moyenne;
                        b_s = Moyenne;

    pixel_s = SDL_MapRGBA(surface->format, r_s,g_s,b_s,a_s);
    putpixel(surface,x,y,pixel_s);
   }
 }

    SDL_UnlockSurface(surface);
}

void Binarisation(SDL_Surface* surface)
{
int x,y;
Uint8 r_s,g_s,b_s,a_s;
Uint32 pixel_s;
SDL_LockSurface(surface);

for (y=0; y < surface->h;y++)
 {
  for ( x=0;x < surface->w;x++)
   {
    pixel_s = getpixel(surface,x,y);
    SDL_GetRGBA(pixel_s,surface->format,&r_s,&g_s,&b_s,&a_s);
    Uint8 Moyenne = (r_s+g_s+b_s) / 3;
                        if(Moyenne < 123)
                        {
                            r_s = 0;
                            g_s = 0;
                            b_s = 0;
                        }
                        else if(Moyenne >= 124)
                        {
                            r_s = 255;
                            g_s = 255;
                            b_s = 255;
                        }
    pixel_s = SDL_MapRGBA(surface->format, r_s,g_s,b_s,a_s);
    putpixel(surface,x,y,pixel_s);
   }
 }
    SDL_UnlockSurface(surface);
}


/*based on maximization of inter-class variance */
void Otsu(SDL_Surface* surface, SDL_Surface* empty)
{
  Uint8 r_s, g_s, b_s, a_s;
  Uint32 pixel_s;
  int moyenne;
  int x_surface = surface->w;
  int y_surface = surface->h;

  int GRAYLEVEL = 256;
  int histogram[GRAYLEVEL];
  double probability[GRAYLEVEL], omega[GRAYLEVEL]; /* prob of graylevels */
  double myu[GRAYLEVEL];   /* mean value for separation */
  double max_sigma, sigma[GRAYLEVEL]; /* inter-class variance */
  int i, x, y; /* Loop variable */
  int threshold; /* threshold for binarization */
  
  //Histogram
  for (i = 0; i < GRAYLEVEL; i++)
    histogram[i] = 0;
  
  for (y = 0; y < y_surface; y++)
  {
    for (x = 0; x < x_surface; x++)
    {
      pixel_s = getpixel(surface,x,y);
      SDL_GetRGBA(pixel_s,surface->format,&r_s,&g_s,&b_s,&a_s);
      moyenne = (r_s + g_s + b_s)/3;
      histogram[moyenne]++;
    }
  }
  
  //calculation of probability density
  for ( i = 0; i < GRAYLEVEL; i ++ )
    probability[i] = (double)histogram[i] / (x_surface * y_surface);
  
  
  //omega & myu generation
  omega[0] = probability[0];
  myu[0] = 0.0;
  for (i = 1; i < GRAYLEVEL; i++)
  {
    omega[i] = omega[i-1] + probability[i];
    myu[i] = myu[i-1] + i*probability[i];
  }
  
  //sigma maximization
  threshold = 0;
  max_sigma = 0.0;
  for (i = 0; i < GRAYLEVEL-1; i++)
  {
    if (omega[i] != 0.0 && omega[i] != 1.0)
      sigma[i] = pow(myu[GRAYLEVEL-1]*omega[i] - myu[i], 2) /
      (omega[i]*(1.0 - omega[i]));
    else
      sigma[i] = 0.0;
    if (sigma[i] > max_sigma)
    {
      max_sigma = sigma[i];
      threshold = i;
    }
  }
  
  printf("\nthreshold = %d\n", threshold);
  
  //binarization output
  Uint8 r, g, b, a;

  for (y = 0; y < y_surface; y++)
  {
    for (x = 0; x < x_surface; x++)
    {
      pixel_s = getpixel(surface, x, y);
      SDL_GetRGBA(pixel_s,surface->format,&r,&g,&b,&a);
      moyenne = (r + g + b)/3;

      if (moyenne > threshold)
      {
        r = 255;
        g = 255;
        b = 255;
      }
      else
      {
        r = 0;
        g = 0;
        b = 0;
      }
      pixel_s = SDL_MapRGBA(surface->format, r,g,b,a);
      putpixel(empty,x,y,pixel_s);
    }
  }
  SDL_UnlockSurface(empty);
}
