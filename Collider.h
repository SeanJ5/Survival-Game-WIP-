#pragma once

#include "SDL2/SDL.h"

typedef struct
{
  int x, y;
  Uint8 w, h;
} Collider;

Collider* Collider_Create(int x, int y, Uint8 w, Uint8 h);
void Collider_Destroy(Collider* c);
