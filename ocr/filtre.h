#ifndef HEADER_FILTRE
#define HEADER_FILTRE

#include <SDL/SDL.h>
#include <glib.h>
#include <gtk/gtk.h>

void Binarisation(SDL_Surface* surface);
void Gray_Scale(SDL_Surface* surface);
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void mainbin(gchar *path);
void Otsu(SDL_Surface* surface, SDL_Surface* empty);
#endif
