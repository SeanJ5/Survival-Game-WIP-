#pragma once

#include "Bitmaps.h"
#include "Screen.h"
#include "stdbool.h"
#include "Level.h"
#include "Collider.h"

#define TILE_SIZE 16
#define TILE_BIT_SHIFT 4

#define TILE_TYPE_NORMAL 0
#define TILE_TYPE_SOLID 1
#define TILE_TYPE_SPECIAL 2

#define TILES_NULL         '\0'
#define TILES_WOODEN_PLANK 'a'
#define TILES_GRASS        'g'
#define TILES_STONE        's'
#define TILES_WATER        'w'

typedef struct Tile
{
  Bitmap* image;
  Uint32 colors[3];
  Uint8 type;
  Uint8 flags;
  Uint16 animationTick;
  void (*Update)(struct Tile*);
} Tile;

void Tiles_InitAll();
void Tiles_UpdateAll();

extern Tile TILES[];
