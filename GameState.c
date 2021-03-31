#include "GameState.h"

Level* level1;
Mob* PLAYER;
Mob* ZOMBIE1;

void GameState_Start()
{
  Tiles_InitAll();

  level1 = Level_Create(50, 50);
  Level_GenerateWorld(level1);

  PLAYER = Mob_CreatePlayer(50, 50);
  ZOMBIE1 = Mob_CreateZombie(75, 50);
}

void GameState_Close()
{
  Level_Destroy(level1);
  Mob_Destroy(PLAYER);
}

void GameState_Update()
{
  TILES_GFX_TIMER++;

  bool UP = KeyStates[SDL_SCANCODE_UP] || KeyStates[SDL_SCANCODE_W];
  bool DOWN = KeyStates[SDL_SCANCODE_DOWN] || KeyStates[SDL_SCANCODE_S];
  bool LEFT = KeyStates[SDL_SCANCODE_LEFT] || KeyStates[SDL_SCANCODE_A];
  bool RIGHT = KeyStates[SDL_SCANCODE_RIGHT] || KeyStates[SDL_SCANCODE_D];

  if(UP) Entity_Move(level1, PLAYER->entity,  0, -1);
  if(DOWN) Entity_Move(level1, PLAYER->entity,  0,  1);
  if(LEFT) Entity_Move(level1, PLAYER->entity, -1,  0);
  if(RIGHT) Entity_Move(level1, PLAYER->entity,  1,  0);
}

void GameState_Render(Screen* screen)
{
  Screen_FocusCamera
  (
    screen,
    PLAYER->entity->collider->x + PLAYER->entity->image->w/2,
    PLAYER->entity->collider->y + PLAYER->entity->image->h/2
  );

  Level_Render(screen, level1);

  Entity_Render(screen, PLAYER->entity, 0);
  Entity_Render(screen, ZOMBIE1->entity, 0);
}














/*
  TREE_LEFT = Entity_Create(50, 50, 8, 16, BITMAPS_TREE_HALF,
  (Uint32[])
  {
    Screen_GetRGB(0x09, 0x39, 0x09),
    Screen_GetRGB(0x71, 0xc3, 0x79),
    Screen_GetRGB(0xa4, 0xa0, 0x5c)
  });

  TREE_RIGHT = Entity_Create(58, 50, 8, 16, BITMAPS_TREE_HALF,
  (Uint32[])
  {
    Screen_GetRGB(0x09, 0x39, 0x09),
    Screen_GetRGB(0x30, 0x84, 0x2e),
    Screen_GetRGB(0x7a, 0x65, 0x41)
  });
*/
