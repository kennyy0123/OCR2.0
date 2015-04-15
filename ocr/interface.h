#ifndef HEADER_INTERFACE
#define HEADER_INTERFACE

#include <stdio.h>
#include <gtk/gtk.h>
#include <SDL/SDL.h>
#include <inttypes.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "filtre.h"
#include "rotation.h"
#include "detection.h"

void CloseWindow(GtkWidget *pWidget, gpointer pData);
void Binarize(GtkWidget *pWidget,gpointer pData);
void CharaDetect(GtkWidget *pWidget, gpointer pData);
void Load(GtkWidget *pWidget,gpointer pData);
void Binarize(GtkWidget *pWidget, gpointer pData);
void CharaDetect(GtkWidget *pWidget, gpointer pData);
void Load(GtkWidget *pWidget, gpointer pData);
void Removechildwidget(GtkWidget *Boxparent);
int init();
void Rotation(GtkWidget *pWidget,gpointer pData);
#endif
