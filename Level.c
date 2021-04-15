#include "Level.h"
#include "Utils.h"

Level* Level_Create(Uint16 w, Uint16 h)
{
  Level* l = malloc(sizeof(Level));
  l->width = w;
  l->height = h;
  l->map = malloc(w * h);
  return l;
}

void Level_Destroy(Level* l)
{
  free(l->map);
  free(l);
}

void Level_GenerateWorld(Level* l)
{
  int y, x;

  for(x = 0; x < l->width * l->height; x++)
    l->map[x] = TILES_WATER;


  for(x = 0; x < 1000; x++)
  {
    l->map[rand()%l->width + rand()%l->height * l->width] = TILES_GRASS;
    l->map[rand()%l->width + rand()%l->height * l->width] = TILES_STONE;
  }
}

signed char Level_CheckTileIntersection(Level* l, int x, int y, Uint8 w, Uint8 h)
{
  for(Uint8 c = 0; c < 4; c++ /* <-- Insert nerdy joke here */)
    if( TILES [ l->map [
          ( x + (w - 1) * (c % 2) ) / TILE_SIZE +
          ( y + (h - 1) * (c / 2) ) / TILE_SIZE * l->width ] ].solid)
          return c;
    return -1;
}

void Level_Render(Screen* s, Level* l)
{
  int xs = MAX(CameraXOffs / TILE_SIZE, 0);
  int ys = MAX(CameraYOffs / TILE_SIZE, 0);
  int xe = MIN((CameraXOffs + s->width ) / TILE_SIZE + 1, l->width);
  int ye = MIN((CameraYOffs + s->height) / TILE_SIZE + 1, l->height);

  char tile;

  for(Uint32 y = ys; y < ye; y++)
    for(Uint32 x = xs; x < xe; x++)
    {
      tile = l->map[x + y * l->width];

      Screen_BlitBitmap
      (
        s, TILES[tile].image, TILES[tile].colors,
           x * TILE_SIZE, y * TILE_SIZE, FLIPX
      );
    }
}
