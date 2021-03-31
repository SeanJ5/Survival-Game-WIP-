#include "Entity.h"

typedef struct
{
  Entity* entity;
  int health;
  int attack;
} Mob;

Mob* Mob_Create(int x, int y, Uint8 w, Uint8 h,
                Bitmap* image, Uint32 colors[3],
                int health, int attack);

void Mob_Destroy(Mob* e);


Mob* Mob_CreatePlayer(int x, int y);
Mob* Mob_CreateZombie(int x, int y);
