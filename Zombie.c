#include "Zombie.h"
#include "Player.h"
#include "stdbool.h"
#include "Animations.h"

Entity* Zombie_CreateZombieEntity(int x, int y)
{
  Entity* e = Entity_Create(x, y, 12, 14, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0xd1, 0x92, 0x00),
    Screen_GetRGB(0x21, 0x91, 0x4e)
  }, Zombie_Update, Zombie_Render);
  return e;
}

void Zombie_Update(Entity* e)
{
/*
  signed char xa, ya;

  xa = ya = 0;

  if(e->collider->y < PLAYER->collider->y) { e->dir = DIR_DOWN;  ya =  1; }
  if(e->collider->y > PLAYER->collider->y) { e->dir = DIR_UP;    ya = -1; }

  if(e->collider->x < PLAYER->collider->x) { e->dir = DIR_RIGHT; xa =  1; }
  if(e->collider->x > PLAYER->collider->x) { e->dir = DIR_LEFT;  xa = -1; }

  Entity_Move(e, xa, ya);
  Animations_HumanWalk(e);
*/
}

void Zombie_Render ( Screen* s, Entity* e )
{
  Entity_Render ( s, e, FLIPX );
}
