#include "Entity.h"
#include "stdbool.h"

Level* Entity_CurrentLevel;

Entity* Entity_Create(int x, int y, Uint8 w, Uint8 h,
                      Bitmap* image, Uint32 colors[3],
                      void (*Update)(struct Entity* e),
                      void (*Render)(Screen* s, struct Entity* e))
{
  Entity* e = malloc(sizeof(Entity));
  e->image = image;
  e->collider = Collider_Create(x, y, w, h);
  e->colors[0] = colors[0];
  e->colors[1] = colors[1];
  e->colors[2] = colors[2];
  e->renderXOffs = 0;
  e->renderYOffs = 0;
  e->Update = Update;
  e->Render = Render;
  return e;
}

void Entity_Destroy(Entity* e)
{
  free(e->collider);
  free(e);
}

void Entity_SetCurrentLevel(Level* l)
{
  Entity_CurrentLevel = l;
}

void Entity_Render(Screen* s, Entity* e, Uint8 flags)
{
  Screen_BlitBitmap(s, e->image, e->colors,
    e->collider->x + e->renderXOffs, e->collider->y + e->renderYOffs, flags);
}

signed char Entity_Move(Level* l, Entity* e, int xa, int ya)
{
  Uint8 add;
  signed char corner;

  /* -X Collision?- */

  corner = Level_CheckTileIntersection
  (
    l, e->collider->x + xa, e->collider->y,
    e->collider->w,         e->collider->h
  );

  if(corner == -1) e->collider->x += xa;
  else
  {
    add = (corner % 2) * e->collider->w;
    e->collider->x = ((e->collider->x + xa + add) / TILE_SIZE * TILE_SIZE)
                      + (TILE_SIZE * ( 1 - (corner % 2) ) - (add));
  }

  /* -X Collision?- */

  corner = Level_CheckTileIntersection
  (
    l, e->collider->x, e->collider->y + ya,
    e->collider->w,         e->collider->h
  );

  if(corner == -1) e->collider->y += ya;
  else
  {
    add = (corner / 2) * e->collider->h;
    e->collider->y = ((e->collider->y + ya + add) / TILE_SIZE * TILE_SIZE)
                      + (TILE_SIZE * ( 1 - (corner / 2) ) - (add));
  }

  return corner;
}
