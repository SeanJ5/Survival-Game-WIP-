#include "Mob.h"

Mob* Mob_Create(int x, int y, Uint8 w, Uint8 h,
                Bitmap* image, Uint32 colors[3],
                int health, int attack)
{
  Mob* m = malloc(sizeof(Mob));
  m->entity = Entity_Create(x, y, w, h, image, colors);
  m->health = health;
  m->attack = attack;
  return m;
}

void Mob_Destroy(Mob* m)
{
  Entity_Destroy(m->entity);
  free(m);
}

Mob* Mob_CreatePlayer(int x, int y)
{
  return Mob_Create(x, y, 12, 14, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0x70, 0x61, 0x5b),
    Screen_GetRGB(0xc0, 0xa2, 0x89)
  }, 100, 10);
}

Mob* Mob_CreateZombie(int x, int y)
{
  return Mob_Create(x, y, 12, 14, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0xd1, 0x92, 0x00),
    Screen_GetRGB(0x21, 0x91, 0x4e)
  }, 100, 10);
}
