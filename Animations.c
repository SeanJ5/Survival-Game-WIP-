#include "Entity.h"

void Animations_HumanWalk(Entity* e)
{
  // For walking animation
  const Uint8 maxTick_H = 10;
  const Uint8 maxTick_V = 15;

  switch(e->dir)
  {
    case DIR_LEFT  : e->animationTick++;
                     if(e->animationTick >= maxTick_H)
                     { e->image = (e->image == BITMAPS_PLAYER_SIDE) ?
                       BITMAPS_PLAYER_SIDE_STEP : BITMAPS_PLAYER_SIDE;
                       e->flipx = FLIPX; e->animationTick = 0;
                     } break;
    case DIR_RIGHT : e->animationTick++;
                     if(e->animationTick >= maxTick_H)
                     { e->image = (e->image == BITMAPS_PLAYER_SIDE) ?
                       BITMAPS_PLAYER_SIDE_STEP : BITMAPS_PLAYER_SIDE;
                       e->flipx = 0; e->animationTick = 0;
                     } break;
    case DIR_UP    : e->image = BITMAPS_PLAYER_UP; e->animationTick++; if(e->animationTick >= maxTick_V) { e->flipx = (e->flipx == 0) ? FLIPX : 0; e->animationTick = 0; } break;
    case DIR_DOWN  : e->image = BITMAPS_PLAYER_DOWN; e->animationTick++; if(e->animationTick >= maxTick_V) { e->flipx = (e->flipx == 0) ? FLIPX : 0; e->animationTick = 0; } break;
  }

  printf("%d\n", e->dir);

  e->renderW = e->image->w;
  e->renderXOffs = (e->image->w - BITMAPS_PLAYER_SIDE->w) / -2;

  if(e->collisionData.tile != TILES_WATER)
  {
    e->renderYOffs = -10;
    e->renderH = e->image->h;
  }
  else
  {
    e->renderYOffs = e->image->h/-2 + 2;
    e->renderH = e->image->h - 7;
  }
}
