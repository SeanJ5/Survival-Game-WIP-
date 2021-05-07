#pragma once

#include "Bitmaps.h"
#include "Collider.h"
#include "Screen.h"
#include "Level.h"
#include "Tiles.h"

extern Level* Entity_CurrentLevel;

#define DIR_DOWN 0
#define DIR_RIGHT 1
#define DIR_UP 2
#define DIR_LEFT 3

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
  Uint8 renderW, renderH;

  // Every entity needs this to update and render
  void (*Update)(struct Entity* e);
  void (*Render)(Screen* s, struct Entity* e);

  // Used by zombies, could be used by other entities
  int targetX, targetY;

  // Current collision info of entity
  Tile_Corner_Couple collisionData;

  Uint16 animationTick;
  signed char dir;
  Uint16 timerTick;

  Uint8 flipx, flipy;

} Entity;

Entity* Entity_Create(int x, int y, Uint8 w, Uint8 h,
                      Bitmap* image, Uint32 colors[3],
                      void (*Update)(struct Entity* e),
                      void (*Render)(Screen* s, struct Entity* e));
void Entity_Destroy(Entity* e);

void Entity_SetCurrentLevel(Level* l);

Tile_Corner_Couple Entity_Move(Entity* e, int xa, int ya);

void Entity_Render(Screen* s, Entity* e, Uint8 flags);
