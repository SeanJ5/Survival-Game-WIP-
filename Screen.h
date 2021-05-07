#ifndef SCREEN_H
#define SCREEN_H

#include "SDL2/SDL.h"
#include "Bitmaps.h"
#include "stdbool.h"

#define FLIPX 1
#define FLIPY 2

extern int CameraXOffs, CameraYOffs;

/*====[( SCREEN STRUCT FOR DRAWING GAME )]====*/
typedef struct Screen
{
  SDL_Surface* surface;
  SDL_Texture* texture;
  SDL_Renderer* renderer;
  Uint32* raster;
  Uint16 width;
  Uint16 height;
} Screen;

/*========[( PROTOTYPES FOR Screen.c )]========*/
Screen* Screen_Create(SDL_Renderer* r, Uint16 w, Uint16 h);
Uint32 Screen_GetRGB(Uint8 r, Uint8 g, Uint8 b);
void Screen_Destroy(Screen* s);
void Screen_DrawToWindow(Screen* screen, SDL_Window* window);
void Screen_BlitBitmap(Screen* s, Bitmap* b, Uint32 colors[], int xp, int yp, Uint8 w, Uint8 h, Uint8 flags);
void Screen_Clear(Screen* s, Uint32 color);
void Screen_FocusCamera(Screen* s, int x, int y);

#endif
