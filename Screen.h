#pragma once

#include "SDL2/SDL.h"
#include "Bitmaps.h"

#define FLIPX 1
#define FLIPY 2

extern int CameraXOffs, CameraYOffs;

typedef struct Screen
{
  Uint32* raster;
  Uint16 width;
  Uint16 height;
} Screen;

Screen* Screen_Create(Uint16 w, Uint16 h);
void Screen_Destroy(Screen* s);
void Screen_DrawToWindow(SDL_Surface* surface, Screen* screen);
Uint32 Screen_GetRGB(Uint8 r, Uint8 g, Uint8 b);
void Screen_BlitBitmap(Screen* s, Bitmap* b, Uint32 colors[], int xp, int yp, Uint8 flags);
void Screen_Clear(Screen* s, Uint32 color);
void Screen_FocusCamera(Screen* s, int x, int y);
