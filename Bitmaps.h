#ifndef BITMAPS
#define BITMAPS
#include "SDL2/SDL.h"

typedef struct Bitmap
{
  Uint8 w, h;
  Uint8* bitmap;
} Bitmap;

extern Bitmap* BITMAPS_PLAYER_DOWN;
extern Bitmap* BITMAPS_PLAYER_UP;
extern Bitmap* BITMAPS_PLAYER_SIDE;
extern Bitmap* BITMAPS_PLAYER_SIDE_STEP;

extern Bitmap* BITMAPS_TILE;
extern Bitmap* BITMAPS_TREE_HALF;

extern Bitmap* BITMAPS_PUDDLE;

Bitmap* Bitmap_Create(Uint8 w, Uint8 h, Uint8 bmp[]);
void Bitmap_Destroy(Bitmap* b);
void Bitmaps_CreateAll();
void Bitmaps_DestroyAll();

#endif
