#include "Player.h"
#include "Input.h"

Entity* Player_CreatePlayerEntity(int x, int y)
{
  return Entity_Create(x, y, 12, 14, BITMAPS_PLAYER_DOWN,
  (Uint32[])
  {
    Screen_GetRGB(0x19, 0x11, 0x02),
    Screen_GetRGB(0x70, 0x61, 0x5b),
    Screen_GetRGB(0xc0, 0xa2, 0x89)
  }, Player_Update, Player_Render);
}

void Player_Update(Entity* e)
{
  bool UP    = KeyStates [ SDL_SCANCODE_UP    ] || KeyStates [SDL_SCANCODE_W ];
  bool DOWN  = KeyStates [ SDL_SCANCODE_DOWN  ] || KeyStates [SDL_SCANCODE_S ];
  bool LEFT  = KeyStates [ SDL_SCANCODE_LEFT  ] || KeyStates [SDL_SCANCODE_A ];
  bool RIGHT = KeyStates [ SDL_SCANCODE_RIGHT ] || KeyStates [SDL_SCANCODE_D ];

  signed char xa = 0, ya = 0;

  if ( UP    ) ya = -1;
  if ( DOWN  ) ya = +1;
  if ( LEFT  ) xa = -1;
  if ( RIGHT ) xa = +1;
  Entity_Move ( Entity_CurrentLevel, e,  xa,  ya );
}

void Player_Render ( Screen* s, Entity* e )
{
  Entity_Render ( s, e, FLIPX );
}
