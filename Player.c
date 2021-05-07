#include "Player.h"
#include "Input.h"
#include "Animations.h"

Entity* Player_CreatePlayerEntity(int x, int y)
{
  Entity* p = Entity_Create(x, y, 8, 4, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0x70, 0x61, 0x5b),
    Screen_GetRGB(0xc0, 0xa2, 0x89)
  }, Player_Update, Player_Render);
  p->renderYOffs = -10;
  return p;
}

void Player_Update(Entity* e)
{
  // Get Input
  const bool UP    = KeyStates [ SDL_SCANCODE_UP    ] || KeyStates [SDL_SCANCODE_W ];
  const bool DOWN  = KeyStates [ SDL_SCANCODE_DOWN  ] || KeyStates [SDL_SCANCODE_S ];
  const bool LEFT  = KeyStates [ SDL_SCANCODE_LEFT  ] || KeyStates [SDL_SCANCODE_A ];
  const bool RIGHT = KeyStates [ SDL_SCANCODE_RIGHT ] || KeyStates [SDL_SCANCODE_D ];

  if( UP || DOWN || LEFT || RIGHT )
  {
    signed char xa = 0, ya = 0;
    const signed char speed = 1;

    if (LEFT)  { xa = -speed; e->dir = DIR_LEFT;  }
    if (RIGHT) { xa = +speed; e->dir = DIR_RIGHT; }
    if (UP)    { ya = -speed; e->dir = DIR_UP;    }
    if (DOWN)  { ya = +speed; e->dir = DIR_DOWN;  }

    e->collisionData = Entity_Move ( e,  xa,  ya );

    Animations_HumanWalk(e);
  }
}

void Player_Render ( Screen* s, Entity* e )
{
  if(e->collisionData.tile == TILES_WATER)
  {
    Screen_BlitBitmap(s, BITMAPS_PUDDLE, TILES[TILES_WATER].colors,
      e->collider->x - 2, e->collider->y - 4,
      BITMAPS_PUDDLE->w, BITMAPS_PUDDLE->h, 0);
  }

  Entity_Render ( s, e, e->flipx);
}
