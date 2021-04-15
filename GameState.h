#include "SDL2/SDL.h"
#include "Screen.h"
#include "Bitmaps.h"
#include "Input.h"
#include "Level.h"
#include "Tiles.h"
#include "Entity.h"

void GameState_Start();
void GameState_Close();
void GameState_Update();
void GameState_Render(Screen* s);
