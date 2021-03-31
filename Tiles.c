#include "Tiles.h"

Tile TILES[256];
Uint8 TILES_GFX_TIMER;

void Tiles_InitTile(char ID, bool solid, Bitmap* b, Uint32 colors[3])
{
  TILES[ID] = (Tile) { .image = b };
  TILES[ID].solid = solid;
  TILES[ID].colors[0] = colors[0];
  TILES[ID].colors[1] = colors[1];
  TILES[ID].colors[2] = colors[2];
}

void Tiles_InitAll()
{
  Tiles_InitTile
  (
    'g', false, BITMAPS_TILE, (Uint32[])
    {
      Screen_GetRGB(0x62, 0xa4, 0x63),
      Screen_GetRGB(0x95, 0xd7, 0x95),
      Screen_GetRGB(0x00, 0x00, 0x00),
    }
  );

  Tiles_InitTile
  (
    'w', false, BITMAPS_TILE, (Uint32[])
    {
      Screen_GetRGB(0x17, 0x17, 0x87),
      Screen_GetRGB(0x41, 0x47, 0xa2),
      Screen_GetRGB(0x00, 0x00, 0x00),
    }
  );

  Tiles_InitTile
  (
    'r', true, BITMAPS_TILE, (Uint32[])
    {
      Screen_GetRGB(0xCC, 0xCC, 0xCC),
      Screen_GetRGB(0x77, 0x77, 0x77),
      Screen_GetRGB(0x00, 0x00, 0x00),
    }
  );
}
