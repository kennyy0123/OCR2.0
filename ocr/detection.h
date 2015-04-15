#ifndef HEADER_DETECT
#define HEADER_DETECT

#include <SDL/SDL.h>
#include <inttypes.h>

int checkColumnLine(SDL_Surface *surface,int y,int hBegin,int hEnd);
void makeCharBox(SDL_Surface *surface,int x,int w, int hBegin,int hEnd);
void findTextLine(SDL_Surface *surface);
int initDetect(/*int argc, char *argv[]*/);
void drawHorizontalLine(SDL_Surface *surface,int y,int wStart,
int wEnd,Uint32 pixel);
void drawVerticalLine(SDL_Surface *surface,int x,int hStart,int hEnd,
Uint32 pixel);
int checkColorLine(SDL_Surface *surface,int y,Uint32 pixel);
int checkWhiteLine(SDL_Surface *surface,int y,int wBegin,int wEnd);
void findBlockHorizontal(SDL_Surface *surface,int x,int y,int w, int h,int d);
void findBlockVertical(SDL_Surface *surface,int x,int y,int w, int h,int d);

#endif
