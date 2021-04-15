#include "Zombie.h"

Entity* Zombie_CreateZombieEntity(int x, int y)
{
  Entity* e = Entity_Create(x, y, 12, 14, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0xd1, 0x92, 0x00),
    Screen_GetRGB(0x21, 0x91, 0x4e)
  }, Zombie_Update, Zombie_Render);
  e -> targetX = rand() % Entity_CurrentLevel -> width;
  e -> targetY = rand() % Entity_CurrentLevel -> height;
  e -> timerTick = 0;
  return e;
}

void Zombie_Update(Entity* e)
{
  signed char xa, ya, corner;

  if(e->collider->x < e->targetX) xa = 1;
  else if(e->collider->x > e->targetX) xa = -1;

  if(e->collider->y < e->targetY) ya = 1;
  else if(e->collider->y > e->targetY) ya = -1;

  corner = Entity_Move(Entity_CurrentLevel, e, xa, ya);

//e->collider->x == e->targetX && e->collider->y == e->targetY
  if(e->timerTick == 200)
  {
    e -> targetX = rand() % Entity_CurrentLevel -> width * TILE_SIZE;
    e -> targetY = rand() % Entity_CurrentLevel -> height * TILE_SIZE;
  }

  e->timerTick++;
  if(e->timerTick > 200) e->timerTick = 0;
}

void Zombie_Render ( Screen* s, Entity* e )
{
  Entity_Render ( s, e, FLIPX );
}
