#include "GameState.h"
#include "Player.h"
#include "Zombie.h"

Level* level1;
Entity* PLAYER;
Entity* ZOMBIE1;

void GameState_Start ()
{
  Tiles_InitAll ();

  level1 = Level_Create ( 50, 50 );
  Level_GenerateWorld ( level1 );
  Entity_SetCurrentLevel(level1); // Sets the current level for all entities

  PLAYER  = Player_CreatePlayerEntity ( 50, 50 );
  ZOMBIE1 = Zombie_CreateZombieEntity ( 75, 50 );
}

void GameState_Close()
{
  Level_Destroy ( level1 );

  Entity_Destroy ( PLAYER );
  Entity_Destroy ( ZOMBIE1 );
}

void GameState_Update ()
{
  Tiles_UpdateAll();

  PLAYER  -> Update(PLAYER);
  ZOMBIE1 -> Update(ZOMBIE1);
}

void GameState_Render ( Screen* screen )
{
  Screen_FocusCamera
  (
    screen,
    PLAYER -> collider -> x + PLAYER -> renderXOffs + PLAYER -> image -> w / 2,
    PLAYER -> collider -> y + PLAYER -> renderYOffs + PLAYER -> image -> h / 2
  );

  Level_Render ( screen, level1 );
  PLAYER  -> Render ( screen, PLAYER );
  ZOMBIE1 -> Render ( screen, ZOMBIE1 );
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
