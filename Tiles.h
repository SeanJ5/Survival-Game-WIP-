#pragma once

#include "Bitmaps.h"
#include "Screen.h"
#include "stdbool.h"
#include "Level.h"
#include "Collider.h"

#define TILE_SIZE 16
#define TILE_BIT_SHIFT 4

#define TILES_WOODEN_PLANK 'a'
#define TILES_GRASS        'g'
#define TILES_ROCK         'r'
#define TILES_WATER        'w'

typedef struct
{
  Bitmap* image;
  Uint32 colors[3];
  bool solid;
} Tile;

void Tiles_InitAll();

extern Tile TILES[];
extern Uint8 TILES_GFX_TIMER;
