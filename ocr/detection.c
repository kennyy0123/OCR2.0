#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "filtre.h"



void drawHorizontalLine(SDL_Surface *surface,int y,int wStart,int wEnd,
Uint32 pixel)
{

    for (int j=wStart;j<wEnd;j++)
    {
        putpixel(surface,j,y,pixel);
    }
}

void drawVerticalLine(SDL_Surface *surface,int x,int hStart,int hEnd,
Uint32 pixel)
{
    for (int j=hStart;j<hEnd;j++)
    {
        putpixel(surface,x,j,pixel);
    }

}

int checkWhiteLine(SDL_Surface *surface,int y,int wBegin,int wEnd)
{
    int meetPixels=1,j=wBegin+1;
    while(j<wEnd&&meetPixels==1)
    {
        if(getpixel(surface,j,y)!=16777215)
        {
            return 0;
        }
        j++;
    }
    return 1;
}

int checkWhiteColumn(SDL_Surface *surface,int x,int hBegin,int hEnd)
{
    int meetPixels=1,j=hBegin+1;
    while(j<hEnd && meetPixels==1)
    {
        if(getpixel(surface,x,j)!=16777215)
        {
            return 0;
        }
        j++;
    }
    return 1;
}



int checkWhitearound(SDL_Surface *surface, int wBegin, int hBegin, int wEnd, 
int hEnd)
{
    int meetPixels=1,j=hBegin+1, i = wBegin+1;
    while(j<hEnd && meetPixels==1)
    {
      while(i < wEnd && meetPixels == 1)
      {
        if(getpixel(surface,i,j)!=16777215)
        {
            return 0;
        }
        i++;
      }
      j++;
      i = wBegin+1;
    }
    return 1;
}

void drawletter(SDL_Surface *surface, int xhg,int yhg,int xbd,int ybd)
{
  int x_surface = surface->w;
  Uint32 pixel_b = 0x000000fff;
  int x = xhg, y = yhg;
  int x1_block; 
  while(checkWhiteColumn(surface, x, yhg, ybd)&& x < x_surface)
    x++;

  x1_block = x;
  while (!checkWhiteColumn(surface, x, yhg,ybd) && x < x_surface) 
    x++;

  drawHorizontalLine(surface,y-1,x1_block,x,pixel_b);
  drawHorizontalLine(surface,ybd,x1_block,x,pixel_b);
  drawVerticalLine(surface, x1_block-1, yhg-1, ybd+1, pixel_b);
  drawVerticalLine(surface, x, yhg-1,ybd+1, pixel_b);
  
  if (x < x_surface)
    drawletter(surface, x+1, yhg, xbd, ybd);
}

void drawblock(SDL_Surface *surface, int xhg, int yhg, int xbd, int ybd)
{
  int x_surface = surface->w;
  int y_surface = surface->h;
  Uint32 pixel_b = 0x00000fff;
  int x = xhg, y = yhg;
  int y1_block; 
  int x1_block; 
  while (checkWhiteLine(surface, y, xhg, xbd) && y < ybd)
    y++;
  y1_block = y;
  while (!checkWhiteLine(surface, y, xhg, xbd) && y < ybd)
    y++;
  while(checkWhiteColumn(surface, x, y1_block, y)&& x < x_surface)
    x++;

  x1_block = x;
  while (!checkWhiteColumn(surface, x, y1_block,y) && x < x_surface) 
    x++;

  drawHorizontalLine(surface,y1_block-1,x1_block,x,pixel_b);
  drawHorizontalLine(surface,y,x1_block,x,pixel_b);
  drawVerticalLine(surface, x, y1_block-1,y+1, pixel_b);
  drawVerticalLine(surface, x1_block-1, y1_block-1, y+1, pixel_b);
  if (y < y_surface && y < ybd)
  {
      drawblock(surface, 0, y+1, x_surface, ybd);
      drawletter(surface, x+1,y1_block,x_surface, y);
  }
  
  printf("x1_block = %d, y1_block = %d, x = %d, y = %d \n", x1_block,y1_block,
  x,y);
}

    int initDetect()
    {
        SDL_Surface *imageDeFond = NULL;
        SDL_Rect positionFond;

        positionFond.x = 0;
        positionFond.y = 0;

        SDL_Init(SDL_INIT_VIDEO);
        imageDeFond = (SDL_LoadBMP("sortie.bmp"));
	//ecran = SDL_SetVideoMode(imageDeFond->w, imageDeFond->h, 32, 
	//SDL_HWSURFACE);
	//SDL_WM_SetCaption("Chargement d'images en SDL", NULL);
        
        drawblock(imageDeFond, 0 , 0, imageDeFond->w, imageDeFond->h);
	SDL_SaveBMP(imageDeFond, "sortie.bmp");
        //drawHorizontalLine(imageDeFond,50,0,imageDeFond->w,0x00000fff);
	//SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

        //SDL_Flip(ecran);
        //pause();

        //SDL_FreeSurface(imageDeFond);
        SDL_Quit();

        return EXIT_SUCCESS;
    }

