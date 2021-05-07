#include "Tiles.h"

Tile TILES [ 256 ];

void Tiles_UpdateAll()
{
  for(int i = 0; i <= 255; i++)
    if(TILES[i].Update != NULL)
      TILES[i].Update(&TILES[i]);
}

void Tiles_InitTile ( char ID, Uint8 type, Bitmap* b, Uint32 colors[3] )
{
  TILES [ ID ] = ( Tile ) { .image = b };
  TILES [ ID ].type = type;
  TILES [ ID ].colors [ 0 ] = colors [ 0 ];
  TILES [ ID ].colors [ 1 ] = colors [ 1 ];
  TILES [ ID ].colors [ 2 ] = colors [ 2 ];
  TILES [ ID ].flags = 0;
  TILES [ ID ].animationTick = 0;
  TILES [ ID ].Update = NULL;
}

// Tile update protos
void Tiles_UpdateWater(Tile* t);
//

void Tiles_InitAll ()
{
  Tiles_InitTile
  (
    'g', TILE_TYPE_NORMAL, BITMAPS_TILE, ( Uint32 [] )
    {
      Screen_GetRGB ( 0x62, 0xa4, 0x63 ),
      Screen_GetRGB ( 0x95, 0xd7, 0x95 ),
      Screen_GetRGB ( 0x00, 0x00, 0x00 ),
    }
  );

  Tiles_InitTile
  (
    'w', TILE_TYPE_SPECIAL, BITMAPS_TILE, ( Uint32 [] )
    {
      Screen_GetRGB ( 0x17, 0x17, 0x87 ),
      Screen_GetRGB ( 0x41, 0x47, 0xa2 ),
      Screen_GetRGB ( 0x00, 0x00, 0x00 ),
    }
  );
  TILES['w'].Update = Tiles_UpdateWater;

  Tiles_InitTile
  (
    's', TILE_TYPE_SOLID, BITMAPS_TILE, ( Uint32 [] )
    {
      Screen_GetRGB ( 0x77, 0x77, 0x77 ),
      Screen_GetRGB ( 0xCC, 0xCC, 0xCC ),
      Screen_GetRGB ( 0x00, 0x00, 0x00 ),
    }
  );
}

void Tiles_UpdateWater(Tile* t)
{
  t->animationTick++;

  if(t->animationTick == 30)
  {
    t->flags = (t->flags == 0) ? FLIPX : 0;
    t->animationTick = 0;
  }

}
