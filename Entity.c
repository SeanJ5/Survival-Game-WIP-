#include "Entity.h"
#include "stdbool.h"

Level* Entity_CurrentLevel;

/*================[( Create new Entity on heap )]================*/
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
  e->renderW = image->w;
  e->renderH = image->h;
  e->Update = Update;
  e->Render = Render;
  e->animationTick = 0;
  e->flipx = e->flipy = 0;
  return e;
  //poo
}

/*====[( Destroy Entity )]====*/
void Entity_Destroy(Entity* e)
{
  free(e->collider);
  free(e);
}

/*====[( Set the level pointer that all entities use )]====*/
void Entity_SetCurrentLevel(Level* l)
{
  Entity_CurrentLevel = l;
}

/*================[( Render Entity )]================*/
void Entity_Render(Screen* s, Entity* e, Uint8 flags)
{
  Screen_BlitBitmap(s, e->image, e->colors,
    e->collider->x + e->renderXOffs, e->collider->y + e->renderYOffs, e->renderW, e->renderH, flags);
}

/*================[( Move Entity and check for collisions )]================*/
Tile_Corner_Couple Entity_Move(Entity* e, int xa, int ya)
{
  Uint8 add;
  Tile_Corner_Couple collisionData;

  /* -X Collision?- */

  collisionData = Level_CheckTileIntersection
  (
    e->collider->x + xa, e->collider->y,
    e->collider->w, e->collider->h
  );

  if(collisionData.corner == -1 || TILES[collisionData.tile].type == TILE_TYPE_SPECIAL) e->collider->x += xa;
  else if(TILES[collisionData.tile].type == TILE_TYPE_SOLID)
  {
    add = (collisionData.corner % 2) * e->collider->w;
    e->collider->x = ((e->collider->x + xa + add) / TILE_SIZE * TILE_SIZE)
                      + (TILE_SIZE * ( 1 - (collisionData.corner % 2) ) - (add));
  }

  /* -Y Collision?- */

  collisionData = Level_CheckTileIntersection
  (
    e->collider->x, e->collider->y + ya,
    e->collider->w, e->collider->h
  );

  if(collisionData.corner == -1 || TILES[collisionData.tile].type == TILE_TYPE_SPECIAL) e->collider->y += ya;
  else if(TILES[collisionData.tile].type == TILE_TYPE_SOLID)
  {
    add = (collisionData.corner / 2) * e->collider->h;
    e->collider->y = ((e->collider->y + ya + add) / TILE_SIZE * TILE_SIZE)
                      + (TILE_SIZE * ( 1 - (collisionData.corner / 2) ) - (add));
  }

  return collisionData;
}
