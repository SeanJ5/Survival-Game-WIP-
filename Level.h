#ifndef LEVEL_H
#define LEVEL_H

#include <stdlib.h>
#include "SDL2/SDL.h"
#include "Tiles.h"
#include "Screen.h"

typedef struct
{
  Uint16 width, height;
  char* map;
} Level;

typedef struct
{
  char tile;
  signed char corner;
} Tile_Corner_Couple;

Level* Level_Create(Uint16 w, Uint16 h);
void Level_Destroy(Level* l);
void Level_GenerateWorld(Level* l);
void Level_Render(Screen* s, Level* l);
Tile_Corner_Couple Level_CheckTileIntersection(int x, int y, Uint8 w, Uint8 h);

#endif
