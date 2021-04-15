#pragma once

#include "Bitmaps.h"
#include "Collider.h"
#include "Screen.h"
#include "Level.h"
#include "Tiles.h"


extern Level* Entity_CurrentLevel;


typedef struct Entity
{
  // Bitmap for entity
  Bitmap* image;

  // Collider for entity
  Collider* collider;

  // The 3 colors to render entity bitmap with
  Uint32 colors[3];

  // Render entity with an offset from its x and y pos
  signed char renderXOffs;
  signed char renderYOffs;

  // Every entity needs this to update and render
  void (*Update)(struct Entity* e);
  void (*Render)(Screen* s, struct Entity* e);

  // Used by zombies, could be used by other entities
  int targetX, targetY;

  Uint16 animationTick;

  Uint16 timerTick;

} Entity;

Entity* Entity_Create(int x, int y, Uint8 w, Uint8 h,
                      Bitmap* image, Uint32 colors[3],
                      void (*Update)(struct Entity* e),
                      void (*Render)(Screen* s, struct Entity* e));
void Entity_Destroy(Entity* e);

void Entity_SetCurrentLevel(Level* l);

signed char Entity_Move(Level* l, Entity* e, int xa, int ya);

void Entity_Render(Screen* s, Entity* e, Uint8 flags);
